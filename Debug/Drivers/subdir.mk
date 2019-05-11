################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/adc.c \
../Drivers/dac.c \
../Drivers/dma.c \
../Drivers/gpio.c \
../Drivers/i2c.c \
../Drivers/pit.c \
../Drivers/pwm.c \
../Drivers/spi.c \
../Drivers/uart.c \
../Drivers/wdog.c 

OBJS += \
./Drivers/adc.o \
./Drivers/dac.o \
./Drivers/dma.o \
./Drivers/gpio.o \
./Drivers/i2c.o \
./Drivers/pit.o \
./Drivers/pwm.o \
./Drivers/spi.o \
./Drivers/uart.o \
./Drivers/wdog.o 

C_DEPS += \
./Drivers/adc.d \
./Drivers/dac.d \
./Drivers/dma.d \
./Drivers/gpio.d \
./Drivers/i2c.d \
./Drivers/pit.d \
./Drivers/pwm.d \
./Drivers/spi.d \
./Drivers/uart.d \
./Drivers/wdog.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


