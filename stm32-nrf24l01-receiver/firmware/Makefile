######################################
TOPDIR := $(shell pwd)
######################################
# target
######################################
TARGET = firmware

######################################
# Posibilities
######################################
ESC=y

######################################
# MCU
######################################
MCU = -mthumb -mcpu=cortex-m3

######################################
# building variables
######################################
# debug build?
DEBUG = 0
# optimization
OPT = -Os

#######################################
# pathes
#############################/src##########
# source path

######################################
# source
######################################
C_SOURCES := src/main.c src/persistent_storage.c src/rc_receiver.c src/rf.c src/spi.c src/crc.c
C_SOURCES += startup/stm32f1/system_stm32f1xx.c


#asm
ASM_SOURCES = startup/stm32f1/startup_stm32f100xb.s

#######################################
# binaries
#######################################
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
CP = arm-none-eabi-objcopy
AR = arm-none-eabi-ar
SZ = arm-none-eabi-size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# macros for gcc
AS_DEFS = 
C_DEFS = -DSTM32F1 -DSTM32F100xB
# includes for gcc
AS_INCLUDES = 
C_INCLUDES = -I src -I startup/stm32f1 -I startup/stm32f1/CMSIS/Include

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
    CFLAGS += -g -gdwarf-2 -DDEBUG
    C_SOURCES += src/uart.c startup/stm32f1/syscalls.c
endif
# Generate dependency information
CFLAGS += -MD -MP -MF .dep/$(@F).d

ifeq ($(ESC),y)
    CFLAGS += -DESC
    C_SOURCES += src/esc.c src/tune.c src/adc.c
endif

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = startup/stm32f1/STM32F100XB_FLASH.ld
# libraries
LIBS =
LIBDIR =
LDFLAGS = $(MCU) --specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(TARGET).elf $(TARGET).hex $(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
#c
OBJECTS = $(C_SOURCES:.c=.o)
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(ASM_SOURCES:.s=.o)
vpath %.s $(sort $(dir $(ASM_SOURCES)))

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: %.s
	$(AS) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

%.hex: %.elf
	$(HEX) $< $@
	
%.bin: %.elf
	$(BIN) $< $@	
	
#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(OBJECTS) $(TARGET).elf $(TARGET).bin $(TARGET).map $(TARGET).hex
  
#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
