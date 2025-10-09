SOURCE    = main
MCPU      = cortex-m3
STARTUP   = startup_stm32f103c8tx.s
LOADER    = STM32F103C8TX_FLASH.ld
OBJCOPY = arm-none-eabi-objcopy

CC = arm-none-eabi-gcc

CFLAGS = -mcpu=$(MCPU) -g3 --specs=nano.specs -mthumb -mfloat-abi=soft -Wall


INCLUDE1 =Drivers/CMSIS/Device/ST/STM32F1xx/Include
INCLUDE2 =Drivers/CMSIS/Include
ST_INCL  =Core/Startup

all: build/main.hex 

build/$(SOURCE).elf: build/$(SOURCE).o $(STARTUP).o $(LOADER) Makefile
	$(CC) -o $@ build/$(SOURCE).o $(STARTUP).o -mcpu=$(MCPU) --specs=nosys.specs -T"$(LOADER)" \
	-Wl,-Map=build/$(SOURCE).map -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb \
	-Wl,--start-group -lc -lm -Wl,--end-group
	arm-none-eabi-size build/$(SOURCE).elf
	
$(STARTUP).o: $(ST_INCL)/$(STARTUP).s Makefile
	$(CC) $(CFLAGS) -DDEBUG -c -x assembler-with-cpp -o $@ $<

build/$(SOURCE).o: $(SOURCE).c Makefile
	$(CC) $< $(CFLAGS) -I$(INCLUDE1) -I$(INCLUDE2) -std=gnu11 \
	-c -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -o $@


build/$(SOURCE).hex: build/$(SOURCE).elf
	$(OBJCOPY) -O ihex $< $@


