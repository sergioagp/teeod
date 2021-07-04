#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <include/tee_client_api.h>
#include <include/tee_defines.h>

#include <unistd.h>

#ifndef __aligned
#define __aligned(x) __attribute__((__aligned__(x)))
#endif
//#include <linux/tee.h>

#include "load_ta.h"


#define MAP_SIZE 4096UL
#define MAP_MASK	(MAP_SIZE-1)

#define write32(X,Y)	*((uint32_t*) X) = (uint32_t) Y
#define read32(X)		*((uint32_t*) X)


#define write32_phys(X,Y)	*((uint32_t*) get_virtual_addr((off_t) X)) = (uint32_t) Y
#define read32_phys(X)		*((uint32_t*) get_virtual_addr((off_t) X))


static void* get_virtual_addr(off_t phy_addr)
{
	int memfd = open("/dev/mem", O_RDWR | O_SYNC);
	if(memfd == -1) {
		printf("Cannot open /dev/mem\r\n");
		return NULL;
	}

	void *map_base = mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, phy_addr & ~MAP_MASK);
	if(map_base == (void*) -1) {
		printf("Cannot map memory to user space\r\n");
		return NULL;
	}
	close(memfd);

	void *map_pl_base = map_base + (phy_addr & MAP_MASK);
	return map_pl_base;
}

/* How many device sequence numbers will be tried before giving up */
#define TEEC_MAX_DEV_SEQ	10


static TEEC_Result teec_pre_process_operation(TEEC_Context *ctx,
			TEEC_Operation *operation,
			struct tee_param *params,
			TEEC_SharedMemory *shms)
{
	for (int n = 0; n < TEEC_CONFIG_PAYLOAD_REF_COUNT; n++) {
		uint32_t param_type = 0;

		param_type = TEEC_PARAM_TYPE_GET(operation->paramTypes, n);
		switch (param_type) {
		case TEEC_NONE:
			break;
		case TEEC_VALUE_INPUT:
		case TEEC_VALUE_OUTPUT:
		case TEEC_VALUE_INOUT:
			params[n].a = operation->params[n].value.a;
			params[n].b = operation->params[n].value.b;
			break;
		case TEEC_MEMREF_TEMP_INPUT:
		case TEEC_MEMREF_TEMP_OUTPUT:
		case TEEC_MEMREF_TEMP_INOUT:
			for(int i=0;i<operation->params[n].tmpref.size/4;i++) {
				static uint32_t *shm_addr=(uint32_t *)TEE_SHM_BASE;
				static uint32_t *buf_addr;
				buf_addr=operation->params[n].tmpref.buffer;
				write32_phys(&shm_addr[i],buf_addr[i]);
				//printf("Addr:0x%x, Addr2:0x%x, data:0x%x\r\n",&shm_addr[i], &buf_addr[i], read32_phys(&shm_addr[i]));
			}

			params[n].a = TEE_SHM_BASE;//operation->params[n].value.a;
			params[n].b = operation->params[n].tmpref.size;

			break;
		case TEEC_MEMREF_WHOLE:
			break;
		case TEEC_MEMREF_PARTIAL_INPUT:
		case TEEC_MEMREF_PARTIAL_OUTPUT:
		case TEEC_MEMREF_PARTIAL_INOUT:
			break;
		default:
			return TEEC_ERROR_BAD_PARAMETERS;
		}
	}

	return TEEC_SUCCESS;
}


static TEEC_Result teec_post_process_operation(TEEC_Operation *operation,
			struct tee_param *params,
			TEEC_SharedMemory *shms)
{
	for (int n = 0; n < TEEC_CONFIG_PAYLOAD_REF_COUNT; n++) {
		uint32_t param_type = 0;

		param_type = TEEC_PARAM_TYPE_GET(operation->paramTypes, n);
		switch (param_type) {
		case TEEC_NONE:
			break;
		case TEEC_VALUE_INPUT:
		case TEEC_VALUE_OUTPUT:
		case TEEC_VALUE_INOUT:
			operation->params[n].value.a=params[n].a;
			operation->params[n].value.b=params[n].b;
			break;
		case TEEC_MEMREF_TEMP_INPUT:
		case TEEC_MEMREF_TEMP_OUTPUT:
		case TEEC_MEMREF_TEMP_INOUT:
			for(int i=0;i<operation->params[n].tmpref.size/4;i++) {
				static uint32_t *shm_addr;
				shm_addr=(uint32_t *) params[n].a;

				static uint32_t *buf_addr;
				buf_addr=(uint32_t *) operation->params[n].tmpref.buffer;

				buf_addr[i] = read32_phys(&shm_addr[i]);
				//printf("Addr:0x%x, Addr2:0x%x, data:0x%x\r\n",&buf_addr[i], &shm_addr[i], read32_phys(&shm_addr[i]));
			}
			//operation->params[n].tmpref.buffer=params[n].a;
			//operation->params[n].tmpref.size=params[n].b;
			break;
		case TEEC_MEMREF_WHOLE:
			break;
		case TEEC_MEMREF_PARTIAL_INPUT:
		case TEEC_MEMREF_PARTIAL_OUTPUT:
		case TEEC_MEMREF_PARTIAL_INOUT:
			break;
		default:
			return TEEC_ERROR_BAD_PARAMETERS;
		}
	}

	return TEEC_SUCCESS;
}


TEEC_Result TEEC_InitializeContext(const char *name, TEEC_Context *ctx)
{

	return TEEC_SUCCESS;
}

void TEEC_FinalizeContext(TEEC_Context *ctx)
{
	if (ctx)
		close(ctx->fd);
}

TEEC_Result TEEC_OpenSession(TEEC_Context *ctx, TEEC_Session *session,
			const TEEC_UUID *destination,
			uint32_t connection_method, const void *connection_data,
			TEEC_Operation *operation, uint32_t *ret_origin)
{
	// Load TA
	char file_name[] = { "/media/sd-mmcblk0p1/8aaaf200-2450-11e4-abe2-0002a5d5c51b.bin" };
	load_ta(file_name);
	
	if(session !=NULL) {
		write32_phys(TEE_SESSIONID_ARGS, session->session_id);
	}

	if(operation !=NULL) {
		write32_phys(TEE_PARAMTYPE_ARGS,operation->paramTypes);
		write32_phys(TEE_PARAM0_0_ARGS, operation->params[0].value.a);
		write32_phys(TEE_PARAM0_1_ARGS, operation->params[0].value.b);
		write32_phys(TEE_PARAM1_0_ARGS, operation->params[1].value.a);
		write32_phys(TEE_PARAM1_1_ARGS, operation->params[1].value.b);
		write32_phys(TEE_PARAM2_0_ARGS, operation->params[2].value.a);
		write32_phys(TEE_PARAM2_1_ARGS, operation->params[2].value.b);
		write32_phys(TEE_PARAM3_0_ARGS, operation->params[3].value.a);
		write32_phys(TEE_PARAM3_1_ARGS, operation->params[3].value.b);
	}
	write32_phys(TEE_OP_ARGS,TEE_OPENSESSION);
	while(read32_phys(TEE_RETURN_ARGS)!=0xBEEF);

	return TEEC_SUCCESS;
}

void TEEC_CloseSession(TEEC_Session *session)
{
	write32_phys(TEE_SESSIONID_ARGS, session->session_id);
	write32_phys(TEE_OP_ARGS,TEE_CLOSESESSION);
	while(read32_phys(TEE_RETURN_ARGS)!=0xBEEF);
}

TEEC_Result TEEC_InvokeCommand(TEEC_Session *session, uint32_t cmd_id,
			TEEC_Operation *operation, uint32_t *error_origin)
{
	struct tee_param params[TEEC_CONFIG_PAYLOAD_REF_COUNT];
	TEEC_SharedMemory shm[TEEC_CONFIG_PAYLOAD_REF_COUNT];

	teec_pre_process_operation(session->ctx, operation, params, shm);

	// Call TA Opensession Command
	if(session !=NULL) {
		write32_phys(TEE_SESSIONID_ARGS, session->session_id);
	}

	if(operation !=NULL) {
		write32_phys(TEE_PARAMTYPE_ARGS,operation->paramTypes);
		write32_phys(TEE_PARAM0_0_ARGS, params[0].a);
		write32_phys(TEE_PARAM0_1_ARGS, params[0].b);
		write32_phys(TEE_PARAM1_0_ARGS, params[1].a);
		write32_phys(TEE_PARAM1_1_ARGS, params[1].b);
		write32_phys(TEE_PARAM2_0_ARGS, params[2].a);
		write32_phys(TEE_PARAM2_1_ARGS, params[2].b);
		write32_phys(TEE_PARAM3_0_ARGS, params[3].a);
		write32_phys(TEE_PARAM3_1_ARGS, params[3].b);
	}
	write32_phys(TEE_CMDID_ARGS, cmd_id);
	write32_phys(TEE_OP_ARGS,TEE_INVOKECMD);
	
	while(read32_phys(TEE_RETURN_ARGS)!=0xBEEF);
	if(operation !=NULL) {	
		params[0].a=read32_phys(TEE_PARAM0_0_ARGS);
		params[0].b=read32_phys(TEE_PARAM0_1_ARGS);
		params[1].a=read32_phys(TEE_PARAM1_0_ARGS);
		params[1].b=read32_phys(TEE_PARAM1_1_ARGS);
		params[2].a=read32_phys(TEE_PARAM2_0_ARGS);
		params[2].b=read32_phys(TEE_PARAM2_1_ARGS);
		params[3].a=read32_phys(TEE_PARAM3_0_ARGS);
		params[3].b=read32_phys(TEE_PARAM3_1_ARGS);


		teec_post_process_operation(operation, params, shm);

	}
	return TEEC_SUCCESS;
}
