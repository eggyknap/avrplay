program: hex
	sudo avrdude -p m48 -c usbtiny -u -U flash:w:interrupt.hex

test:
	sudo avrdude -c usbtiny -p m48 -v

clean:
	rm *.o *.lst *.map

compile: interrupt.c
	avr-gcc -g -c -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=8000000 -Wa,-adhlns=interrupt.lst -mmcu=atmega48 -std=gnu99 interrupt.c -o interrupt.o

link: compile
	avr-gcc -g -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=8000000 -Wa,-adhlns=ada-blink.o -mmcu=atmega48 -std=gnu99 interrupt.o --output interrupt.elf -Wl,-Map=%.map,--cref

hex: link
	avr-objcopy -O ihex -R .eeprom interrupt.elf interrupt.hex
