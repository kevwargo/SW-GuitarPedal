CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
CUBE_PATH=/mnt/flame/soft/stm32/STM32Cube_FW_F3_V1.1.0

CFLAGS=-c -g -std=c99 -Wall -mcpu=cortex-m4 -mlittle-endian -mthumb -DSTM32F334x8 -Os -ffunction-sections -fdata-sections
CFLAGS+=-Iinclude
CFLAGS+=-I$(CUBE_PATH)/Drivers/CMSIS/Device/ST/STM32F3xx/Include
CFLAGS+=-I$(CUBE_PATH)/Drivers/CMSIS/Include
CFLAGS+=-I$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Inc
CFLAGS+=-I$(CUBE_PATH)/Drivers/BSP/STM32F3xx-Nucleo 

LDFLAGS=-mcpu=cortex-m4 -mlittle-endian -mthumb
LDFLAGS+=-Wl,--start-group
LDFLAGS+=-lm
LDFLAGS+=-Wl,--end-group
LDFLAGS+=-static
LDFLAGS+=-Wl,-cref,-u,Reset_Handler
LDFLAGS+=-Wl,--gc-sections
LDFLAGS+=-Wl,--defsym=malloc_getpagesize_P=0x1000 

LDFLAGS+=-Tetc/stm32f30_flash.ld
# LDFLAGS+=-Tetc/STM32F334X8_FLASH.ld

SRCS=src/main.c
SRCS+=src/misc.c
SRCS+=src/led.c
SRCS+=src/adc.c
SRCS+=src/dac.c
SRCS+=src/button.c
SRCS+=src/timer.c

SRCS+=src/system_stm32f3xx.c
SRCS+=src/startup_stm32f334x8.s
SRCS+=src/stm32f3xx_it.c
# SRCS+=src/stm32f3xx_hal_msp.c

SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rcc_ex.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_gpio.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dma.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cortex.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_adc_ex.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_can.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_cec.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_comp.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_crc.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dac.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_dac_ex.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_flash.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_sram.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_nor.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_nand.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pccard.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_hrtim.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2c.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_i2s.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_irda.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_iwdg.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_opamp.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pcd.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_pwr.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_rtc.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_sdadc.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_smartcard.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_smbus.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_spi.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tim_ex.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_tsc.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_uart.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_usart.c
# SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal_wwdg.c
SRCS+=$(CUBE_PATH)/Drivers/STM32F3xx_HAL_Driver/Src/stm32f3xx_hal.c
SRCS+=$(CUBE_PATH)/Drivers/BSP/STM32F3xx-Nucleo/stm32f3xx_nucleo.c





.PHONY: clean
.PHONY: all

OBJS=$(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

all: main.bin

define DefineRule =
$(addprefix obj/, $(addsuffix .o, $(notdir $(basename $(1))))): $(1)
	$$(CC) $$(CFLAGS) $$< -o $$@
endef

$(foreach src, $(SRCS), $(eval $(call DefineRule, $(src))))

main.bin: obj/main.elf
	$(OBJCOPY) -Obinary $^ $@

obj/main.elf: $(OBJS)
	$(LD) $(LDFLAGS) -Wl,-Map=etc/main.map -o $@ $^

clean:
	rm -rf obj/*
