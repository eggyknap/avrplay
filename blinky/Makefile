program: hex
	sudo avrdude -p m48 -c usbtiny -u -U flash:w:ada-blinky.hex

test:
	sudo avrdude -c usbtiny -p m48 -v

clean:
	rm *.o *.lst *.map

compile: ada-blinky.c
	avr-gcc -c -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=8000000 -Wa,-adhlns=ada-blinky.lst -mmcu=atmega48 -std=gnu99 ada-blinky.c -o ada-blinky.o

link: compile
	avr-gcc -I. -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes -DF_CPU=8000000 -Wa,-adhlns=ada-blink.o -mmcu=atmega48 -std=gnu99 ada-blinky.o --output ada-blinky.elf -Wl,-Map=%.map,--cref

hex: link
	avr-objcopy -O ihex -R .eeprom ada-blinky.elf ada-blinky.hex
