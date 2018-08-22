###############################################################################
# Makefile for the project 7bit_Hex_Counter_polling
###############################################################################

## General Flags
PROJECT = 7bit_Hex_Counter_polling
MCU = atmega32
TARGET = 7bit_Hex_Counter_polling.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2        -DF_CPU=16000000UL -O2 -fsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=7bit_Hex_Counter_polling.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = 7bit_Hex_Counter_polling.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) 7bit_Hex_Counter_polling.hex 7bit_Hex_Counter_polling.eep 7bit_Hex_Counter_polling.lss size

## Compile
7bit_Hex_Counter_polling.o: ../7bit_Hex_Counter_polling.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) 7bit_Hex_Counter_polling.elf dep/* 7bit_Hex_Counter_polling.hex 7bit_Hex_Counter_polling.eep 7bit_Hex_Counter_polling.lss 7bit_Hex_Counter_polling.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

