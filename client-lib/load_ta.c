#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>


#include "contiguousMalloc.h"
#include "load_ta.h"

//regs for cdma to transfer data to main BRAM
#define BRAMLoader_CONFIG 	    0xA0010000
#define BRAML_OFFSET_ADDR_SRC	0x00000000
#define BRAML_OFFSET_ADDR_DEST	0x00000004
#define BRAML_OFFSET_SIZE		0x00000008
#define BRAML_OFFSET_TRIG 		0x0000000C
#define BRAML_OFFSET_DONE	 	0x0000000C
#define BRAMLoader_NMR_ARGS	    0x00000005


//CONSTANTS
#define CDMA_AXI_CONFIG 0xA0000000 	//used to config cache coherency
#define BRAM 			0xA0020000
#define TRANSFER_SIZE 	1024 // 8*4bytes

//CDMA Registers
#define CDMACR	0x00
#define CDMASR	0x04
#define CDMASR_IDLE_MASK 0x0002
#define SA		0x18
#define DA		0x20
#define BTT		0x28

long int filetobuffer(char file_name[], void* buffer)
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int sizefile = ftell(fp);

    /* Seek to the beginning of the file */
    fseek(fp, 0, SEEK_SET);

    /* Read and display data */
    fread(buffer, sizefile, 1, fp);

    // closing the file
    fclose(fp);
    return 0;
}

long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long int res = ftell(fp);

    // closing the file
    fclose(fp);
    return res;
}

void writel(uint32_t data, uint32_t* address)
{
	*address=data;
}

uint32_t readl(uint32_t* address)
{
	return *address;
}


static uint32_t bram_loader(unsigned int  start_address, unsigned int  size)
{

	int fd = open("/dev/mem", O_RDWR | O_SYNC);
	/* Map one page of memory that contains the BSC
	   control register */
	void* bramloader_addr = mmap(NULL, BRAMLoader_NMR_ARGS*sizeof(uint32_t), PROT_READ|PROT_WRITE,
					 MAP_SHARED, fd, BRAMLoader_CONFIG);
	close(fd);

	if(bramloader_addr == MAP_FAILED)
	{
		printf("mmap failed\n");
		return -1;
	}
	// Enable snooping of APU caches from CCI
	// No need, for more info: https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842098/Zynq+UltraScale+MPSoC+Cache+Coherency
	// Enable snooping of APU caches from CCI
	//writeData((unsigned int *) 0xFD6E4000,0x1);

	//ADDR Source
	//printf("Config BRAMLoader:ADDR Source bramaddr:0x%x\r\n",(unsigned int)bramloader_addr);
    writel(start_address,bramloader_addr+BRAML_OFFSET_ADDR_SRC);

	//Size
	// printf("Config BRAMLoader:SIZE\r\n");
     writel(size, bramloader_addr+BRAML_OFFSET_SIZE);
	// // //printf("size:0x%08x\r\n", *((uint32_t *) BRAMLCONF_SIZE));

	//Trigger
	// printf("DONE reg BRAMLoader:0x%x\r\n", readl(bramloader_addr+BRAML_OFFSET_DONE));
	// printf("Config BRAMLoader:Trigger\r\n");
    writel(0x1, bramloader_addr+BRAML_OFFSET_TRIG);
    // waiting to finish
	while(readl(bramloader_addr+BRAML_OFFSET_DONE) == 0);
	//printf("Config BRAMLoader:Done\r\n");

    return 0;
}


int load_ta(char file_name[]){
	long int filesize = findSize(file_name);
	// if (filesize != -1)
	//printf("Size of the file is %ld bytes \n", filesize);

    size_t reqSize = (filesize%getpagesize()+1)*getpagesize();//pow(2, 26); //64 MiB
    uintptr_t phys_addr;
    void* userspace = mallocContiguous(reqSize, &phys_addr);
    if (userspace == NULL){
        printf("Failed to aquire memory!\n");
        exit(EXIT_FAILURE);
    }
    memset(userspace, 1, reqSize);
    // printf("Aquired %zu memory!\n", (size_t)(reqSize));
    // printf("\tPhysical address: %p\n", (void*)phys_addr);
    // printf("\tUserspace address: %p\n", userspace);

	filetobuffer(file_name, userspace);
	// if (return_cpy != -1)
	// 	printf("Copy to allocated buffer successfully!!\n");

	bram_loader(phys_addr, filesize);

    if (freeContiguous(phys_addr, userspace, reqSize) != 0){
        printf("Failed to free memory!\n");
        return -1;
    }
    return 0;
}

