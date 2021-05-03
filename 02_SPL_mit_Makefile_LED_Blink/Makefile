# based on https://hackaday.com/2016/03/22/embed-with-elliot-arm-makefile-madness/
# https://github.com/hexagon5un/embed_with_elliot-ARM_makefiles_example

.PHONY: all flash size clean distclean

# Cross-compilation commands
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-gcc
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

## Platform and optimization options
CFLAGS = -c -fno-common -Os -g -mcpu=cortex-m4 -mthumb
CFLAGS += -DSTM32F469_479xx
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -Wall -ffunction-sections -fdata-sections -fno-builtin
CFLAGS += -Wno-unused-function -ffreestanding

#LFLAGS = -TSTM32F479NIHx_FLASH.ld -nostartfiles -Wl,--gc-sections
LFLAGS = -TSTM32F479NIHx_FLASH.ld -Wl,--gc-sections

## Library headers
## STM32F4xx_DSP_StdPeriph_Lib_V1.8.0/Libraries/ kopiert
CFLAGS += -I./
CFLAGS += -I./Libraries/CMSIS/Device/ST/STM32F4xx/Include/
CFLAGS += -I./Libraries/CMSIS/Include/
CFLAGS += -I./Libraries/STM32F4xx_StdPeriph_Driver/inc/

# our code
OBJS  = main.o

# AW: So wie ich das lese hat der "startup code" (Assembler) low-level Initialisierungen,
# die alle stattfinden müssen bevor main() aufgerufen wird. Sollte man nicht antasten
STARTUP = ./Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f469_479xx.s

## Library objects
OBJS += ./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.o
OBJS += ./Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.o
OBJS += ./Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o

## Rules
all: main.bin size flash

%.bin: %.elf
	$(OBJCOPY) --strip-unneeded -O binary $< $@

main.elf: $(OBJS) STM32F479NIHx_FLASH.ld
	$(LD) $(LFLAGS) -o main.elf $(OBJS) $(STARTUP)

## Convenience targets
# st-flash ist in debian in stlink-tools
flash: main.bin
	st-flash --reset write $< 0x8000000

size: main.elf
	$(SIZE) $<

clean:
	-rm -f $(OBJS) main.lst main.elf main.hex main.map main.bin main.list

distclean: clean
	-rm -f *.o core.a $(CORE_LIB_OBJS) $(CORE_LOCAL_LIB_OBJS)
