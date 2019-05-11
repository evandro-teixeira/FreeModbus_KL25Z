################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/port/portevent.c \
../Middlewares/modbus/port/portserial.c \
../Middlewares/modbus/port/porttimer.c 

OBJS += \
./Middlewares/modbus/port/portevent.o \
./Middlewares/modbus/port/portserial.o \
./Middlewares/modbus/port/porttimer.o 

C_DEPS += \
./Middlewares/modbus/port/portevent.d \
./Middlewares/modbus/port/portserial.d \
./Middlewares/modbus/port/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/port/%.o: ../Middlewares/modbus/port/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


