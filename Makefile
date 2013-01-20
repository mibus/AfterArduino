MCU=atmega328p
AVRDUDE_MCU=m328p

all: lca2013-mibus.hex

clean:
	rm lca2013-mibus.hex
flash: lca2013-mibus.hex
	avrdude -c usbtiny -p ${AVRDUDE_MCU} -U flash:w:lca2013-mibus.hex

%.o: %.c
	avr-gcc -g -Os -c -mmcu=${MCU} $*.c
%.elf: %.o
	avr-gcc -mmcu=atmega328p $+ -o $@
%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $+ $@
