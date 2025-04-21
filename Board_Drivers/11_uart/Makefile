CROSS_COMPILE 	:= arm-linux-gnueabihf-
TARGET			:= uart
CC 				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

INCLUDIRS		:= 	imx6ull \
					bsp/clk \
					bsp/led \
					bsp/delay \
					bsp/key	\
					bsp/gpio \
					bsp/int	\
					bsp/epittimer \
					bsp/uart \
					stdio/include

SRCDIRS			:= 	project \
					bsp/clk \
					bsp/led \
					bsp/delay \
					bsp/key	\
					bsp/gpio \
					bsp/int \
					bsp/epittimer \
					bsp/uart \
					stdio/lib
					

LIBPATH			:= -lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

VPATH			:= $(SRCDIRS)

INCLUDE			:= $(patsubst %, -I %,$(INCLUDIRS))

SRC_S			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s ))
SRC_C			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c ))

OBJ				:= $(patsubst %, obj/%, $(notdir $(SRC_S:.s=.o)) $(notdir $(SRC_C:.c=.o)))

$(TARGET).bin	: $(OBJ)
	$(LD) -T imx6ull.ld $^ -o $(TARGET).elf $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis


obj/%.o: %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin $(INCLUDE) -c -O2 $< -o $@

obj/%.o: %.s
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin $(INCLUDE) -c -O2 $< -o $@

.PHONY: clean print

clean:
	rm -rf $(OBJ) $(TARGET).bin $(TARGET).dis $(TARGET).elf load.imx

	
print:
	@echo SRC_S = $(SRC_S)
	@echo SRC_C = $(SRC_C)
	@echo OBJ = $(OBJ)
