################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/rtu/mbcrc.c \
../Middlewares/modbus/rtu/mbrtu.c 

OBJS += \
./Middlewares/modbus/rtu/mbcrc.o \
./Middlewares/modbus/rtu/mbrtu.o 

C_DEPS += \
./Middlewares/modbus/rtu/mbcrc.d \
./Middlewares/modbus/rtu/mbrtu.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/rtu/%.o: ../Middlewares/modbus/rtu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


