CROSS_COMPILE	:=/home/spereira/opt/Xilinx/Vitis/2020.1/gnu/aarch64/lin/aarch64-linux/bin/aarch64-linux-gnu-

CC      := $(CROSS_COMPILE)gcc
LD      := $(CROSS_COMPILE)ld
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
READELF := $(CROSS_COMPILE)readelf

OBJS += tee_client_api.o load_ta.o contiguousMalloc.o

CFLAGS	+= -Wl,-T -Wall -I. -Iinclude/

LIBRARY = libteeodc.a

.PHONY: all
all: $(LIBRARY)

$(LIBRARY): $(OBJS)
	$(AR) rcs $@ $^

.PHONY: clean
clean:
	rm -f *.o $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
