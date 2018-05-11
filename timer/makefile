##################################
# stm32 Makefile
##################################

CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
CP = arm-none-eabi-objcopy

LIBPATH = ../

LKR_SCRIPT = stm32f407vg.ld
FAMILY = STM32F40_41xxx
INCLUDES =  -I$(LIBPATH)CMSIS/Device/ST/STM32F4xx/Include/
INCLUDES +=	-I$(LIBPATH)CMSIS/Include/

CFLAGS  = -c -fno-common -nostdlib -fno-builtin -ffreestanding -g
CFLAGS  += -mcpu=cortex-m4 -mthumb -D$(FAMILY) $(INCLUDES) -DARM_MATH_CM4
LFLAGS  = -nostartfiles -T$(LKR_SCRIPT)
LFLAGS += -Map=test.map

 
all: blink.elf

system.o: system.c
	$(CC) $(CFLAGS) -O0 -o $@ $<
	
main.o: main.c
	$(CC) $(CFLAGS) -O0 -o $@ $<	

blink.elf: main.o system.o 
	$(LD) $(LFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.elf *.bin

debug:
	arm-none-eabi-gdb
