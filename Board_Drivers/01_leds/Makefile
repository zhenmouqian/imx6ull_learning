leds.bin: leds.elf
	arm-linux-gnueabihf-objcopy -O binary -g -S leds.elf leds.bin
leds.elf: leds.o
	arm-linux-gnueabihf-ld -Ttext 0x87800000 leds.o -o leds.elf
leds.o: leds.s
	arm-linux-gnueabihf-gcc -g -c leds.s -o leds.o

clean:
	rm *.o
	rm *.elf
	rm *.bin