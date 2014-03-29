PROGRAM=test
SOURCES=$(PROGRAM).c pcd8544.c
INCLUDE=.
CC=$(HOME)/toolchains/avr8-gnu-toolchain-linux_x86_64/bin/avr-gcc
OBJCOPY=$(HOME)/toolchains/avr8-gnu-toolchain-linux_x86_64/bin/avr-objcopy
OBJDUMP=$(HOME)/toolchains/avr8-gnu-toolchain-linux_x86_64/bin/avr-objdump
SIZE=$(HOME)/toolchains/avr8-gnu-toolchain-linux_x86_64/bin/avr-size
AVRDUDE=avrdude
MMCU=atxmega16a4u
DEVICE=x16a4u
F_CPU=16000000

PROGFLAGS= -p$(DEVICE) -c avrisp2 -P usb -U flash:w:$(PROGRAM).hex:i -B 1

CFLAGS=-mmcu=$(MMCU) -Wall -Os -g -std=c99 -DF_CPU=$(F_CPU) 

all: $(PROGRAM).hex $(PROGRAM).lst

$(PROGRAM).hex: $(PROGRAM).out
	$(OBJCOPY) -j .text -j .data -O ihex $(PROGRAM).out $(PROGRAM).hex
	$(SIZE) -C $(PROGRAM).out --mcu=$(DEVICE)

$(PROGRAM).lst: $(PROGRAM).hex
	$(OBJDUMP) -h -S $(PROGRAM).out > $(PROGRAM).lst

$(PROGRAM).out: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROGRAM).out $(SOURCES) -I$(INCLUDE)

flash: $(PROGRAM).hex
	$(AVRDUDE) -p $(DEVICE) -c avrisp2 -B 1 parms
	$(AVRDUDE) $(PROGFLAGS)

clean:
	rm -f $(PROGRAM).lst
	rm -f $(PROGRAM).out
	rm -f $(PROGRAM).hex
