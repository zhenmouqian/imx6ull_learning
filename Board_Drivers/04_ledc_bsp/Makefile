CROSS_COMPILE 	:= arm-linux-gnueabihf-
TARGET			:= ledc
CC 				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld
OBJCOPY			:= $(CROSS_COMPILE)objcopy
OBJDUMP			:= $(CROSS_COMPILE)objdump

INCLUDIRS		:= 	imx6ull \
					bsp/clk \
					bsp/led \
					bsp/delay

SRCDIRS			:= 	project \
					bsp/clk \
					bsp/led \
					bsp/delay

VPATH			:= $(SRCDIRS)

INCLUDE			:= $(patsubst %, -I %,$(INCLUDIRS))

SRC_S			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s ))
SRC_C			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c ))

OBJ				:= $(patsubst %, obj/%, $(notdir $(SRC_S:.s=.o)) $(notdir $(SRC_C:.c=.o)))

$(TARGET).bin	: $(OBJ)
	$(LD) -T ledc.ld $^ -o $(TARGET).elf
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis


obj/%.o: %.c
	$(CC) -Wall -nostdlib $(INCLUDE) -c -O2 $< -o $@

obj/%.o: %.s
	$(CC) -Wall -nostdlib $(INCLUDE) -c -O2 $< -o $@

.PHONY: clean print

clean:
	rm -rf $(OBJ)

	
print:
	@echo SRC_S = $(SRC_S)
	@echo SRC_C = $(SRC_C)
	@echo OBJ = $(OBJ)
