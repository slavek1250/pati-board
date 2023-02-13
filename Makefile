# Makefile for programming the ATtiny45

DEVICE		= attiny45
CLOCK		= 1000000
PROGRAMMER 	= -c usbasp
SRC			= *.cpp

# For ATTiny45, 1Mhz int osc. with watch-dog
# see http://www.engbedded.com/fusecalc/
FUSES	= -U lfuse:w:0x62:m -U hfuse:w:0xcf:m -U efuse:w:0xff:m

# Tune the lines below only if you know what you are doing:
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) -std=gnu++11 -Xlinker -Map=build/main.map

# symbolic targets:
all:	main.hex

flash:
	$(AVRDUDE) -U flash:w:build/main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

clean:
	rm -f build

# file targets:
main.elf: $(SRC)
	rm -rf build
	mkdir build
	$(COMPILE) -o build/main.elf $(SRC)

main.hex: main.elf
	rm -f build/main.hex
	avr-objcopy -j .text -j .data -O ihex build/main.elf build/main.hex
	avr-size --format=avr --mcu=$(DEVICE) build/main.elf

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d build/main.elf
