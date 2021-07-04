CC      ?= $(CROSS_COMPILE)gcc
LD      ?= $(CROSS_COMPILE)ld
AR      ?= $(CROSS_COMPILE)ar
NM      ?= $(CROSS_COMPILE)nm
OBJCOPY ?= $(CROSS_COMPILE)objcopy
OBJDUMP ?= $(CROSS_COMPILE)objdump
READELF ?= $(CROSS_COMPILE)readelf

OBJS += main.o tx.o

CFLAGS += -Wall -I../ta/include -I./include -I$(TEEC_EXPORT)/include
#Add/link other required libraries here
LDFLAGS += -L$(TEEC_EXPORT) -lteeodc

BINARY = bitcoin_wallet

.PHONY: all
all: $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) main.c tx.c -o wallet $(LDFLAGS)
	$(CC) -o main main.o tx.o $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BINARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

