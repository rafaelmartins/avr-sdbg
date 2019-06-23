# programmer and mcu settings
AVRDUDE_PROGRAMMER ?= usbtiny
AVRDUDE_PORT ?= usb
AVR_MCU ?= attiny85
AVR_CPU_FREQUENCY ?= 8000000UL

AVRDUDE = avrdude
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

CFLAGS = \
	-std=gnu99 \
	-mmcu=$(AVR_MCU) \
	-DF_CPU=$(AVR_CPU_FREQUENCY) \
	-Os \
	-funsigned-char \
	-funsigned-bitfields \
	-fpack-struct \
	-fshort-enums \
	-fno-unit-at-a-time \
	-Wall \
	-Wextra \
	-Werror \
	$(EXTRA_CFLAGS) \
	$(NULL)

SOURCES = \
	test.c \
	asdbg.c \
	$(NULL)

HEADERS = \
	asdbg.h \
	$(NULL)

DEBUG_CFLAGS = \
	-DASDBG_ENABLE \
	-DASDBG_ENABLE_BYTE_FUNCS=1 \
	-DASDBG_ENABLE_BYTE_NL_FUNCS=1 \
	-DASDBG_ENABLE_BYTE_VAR_FUNCS=1 \
	$(NULL)

ifndef RELEASE
EXTRA_CFLAGS = $(DEBUG_CFLAGS)
endif

all: firmware.hex

%.hex: %.elf
	$(OBJCOPY) \
		-O ihex \
		-j .data \
		-j .text \
		$< \
		$@

%.elf: $(SOURCES) $(HEADERS) Makefile
	$(CC) \
		$(CFLAGS) \
		$(SOURCES) \
		-o $@
	@$(MAKE) --no-print-directory size

size: firmware.elf
	@echo;$(SIZE) \
		--mcu=$(AVR_MCU) \
		-C $<

flash: firmware.hex
	$(AVRDUDE) \
		-p $(AVR_MCU) \
		-c $(AVRDUDE_PROGRAMMER) \
		-P $(AVRDUDE_PORT) \
		-U flash:w:$<

clean:
	-$(RM) \
		firmware.elf \
		firmware.hex

.PHONY: all size flash clean
