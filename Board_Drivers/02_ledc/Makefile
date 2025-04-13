obj		:= start.o main.o 
ld		:= arm-linux-gnueabihf-ld
gcc		:= arm-linux-gnueabihf-gcc
objdump	:= arm-linux-gnueabihf-objdump
objcopy	:= arm-linux-gnueabihf-objcopy
target	:= ledc.bin

$(target): $(obj)
	$(ld) -T ledc.ld $^ -o ledc.elf
	$(objcopy) -O binary -S ledc.elf $@
	$(objdump) -D -m arm ledc.elf > ledc.dis

%.o:%.c
	$(gcc) -Wall $< -c -o $@ 

%.o:%.s
	$(gcc) -Wall $< -c -o $@ 

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis