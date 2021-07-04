TARGET			= $(BINARY)

#ta-dev-kit-dir	?= $(shell pwd)
LD_SCRIPT		:= $(ta-dev-kit-dir)/arch/cortex-m1/linker.ld

#############################################################
# Toolchain definitions
#############################################################

CROSS_COMPILE ?= arm-none-eabi-
AS			:=	$(CROSS_COMPILE)as
CC			:=	$(CROSS_COMPILE)gcc
LD			:=	$(CROSS_COMPILE)ld
OBJDUMP		:=	$(CROSS_COMPILE)objdump
OBJCOPY		:=	$(CROSS_COMPILE)objcopy
READELF		:=	$(CROSS_COMPILE)readelf
GDB			:=	$(CROSS_COMPILE)gdb
SIZE		:=	$(CROSS_COMPILE)size
SSTRIP		:=	$(CROSS_COMPILE)strip

#############################################################
# TEEOD declaration
#############################################################
INCLUDES 	+= -I$(ta-dev-kit-dir)/
INCLUDES 	+= -I$(ta-dev-kit-dir)/arch/cortex-m1
INCLUDES 	+= -I$(ta-dev-kit-dir)/arch/
INCLUDES 	+= -I$(ta-dev-kit-dir)/libutee/include

ASM_SRCS 	+= $(ta-dev-kit-dir)/entry.S
ASM_SRCS 	+= $(ta-dev-kit-dir)/tee_isr.S


C_SRCS		+= $(ta-dev-kit-dir)/libutee/tee_api.c
C_SRCS		+= $(ta-dev-kit-dir)/libutee/tee_api_operations.c
C_SRCS		+= $(ta-dev-kit-dir)/tee.c
C_SRCS		+= $(ta-dev-kit-dir)/arch/newlib.c 

#############################################################
# TA Files
#############################################################
INCLUDES	+= $(addprefix -I$(LOCAL_PATH)/, $(global-incdirs-y))
C_SRCS		+= $(addprefix $(LOCAL_PATH)/, $(srcs-y))


#############################################################
# Objects declaration
#############################################################

OBJECTS += $(ASM_SRCS:.S=.o)
OBJECTS += $(C_SRCS:.c=.o)
vpath %.S $(sort $(dir $(ASM_SRCS)))
vpath %.c $(sort $(dir $(C_SRCS)))

TARGET_OBJS := $(TARGET).elf 
TARGET_OBJS += $(TARGET).hex
TARGET_OBJS += $(TARGET).bin
TARGET_OBJS += $(TARGET).lst
TARGET_OBJS += $(TARGET).coe

#############################################################
# Flags definitions
#############################################################

MCUFLAGS	+= -march=armv6s-m 
MCUFLAGS	+= -mcpu=cortex-m1

LDFLAGS		+= -T $(LD_SCRIPT)
LDFLAGS 	+= -static $(MCUFLAGS)
LDFLAGS		+= -mthumb
LDFLAGS 	+= -nostartfiles
LDFLAGS		+= -specs=nano.specs -specs=nosys.specs
LDFLAGS 	+= -Xlinker --gc-sections


CFLAGS		+= -g
CFLAGS		+= -ffunction-sections -fdata-sections -fomit-frame-pointer
CFLAGS		+= $(MCUFLAGS)
CFLAGS		+= $(INCLUDES)
CFLAGS		+= -O0



# default rule: build all
.PHONY: all clean
all: $(TARGET_OBJS)

clean:
	rm -f $(TARGET_OBJS) $(OBJECTS)
	echo $(TA_PATH)

# wildcard rules
%.o: %.S Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).elf: $(OBJECTS) $(LINK_DEPS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

%.hex: %.elf
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

%.lst: %.elf
	$(OBJDUMP) --all-headers --demangle --disassemble --file-headers --wide -D $< > $@

%.coe: %.bin
	python3 $(ta-dev-kit-dir)/tools/bintocoe.py $< $@ 