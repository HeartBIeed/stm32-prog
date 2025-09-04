

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size


CFLAGS=-mcpu=cortex-m0 -mthumb -O2 -Wall -ffreestanding -nostdlib
LDFLAGS=-Tstm32f030x6.ld -nostdlib -Wl,--gc-sections


OBJS=main.o system_stm32f0xx.o startup_stm32f030x6.o


all: main.bin main.hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

main.elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.hex: main.elf
	$(OBJCOPY) -O ihex $< $@

