################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/ascii/mbascii.c 

OBJS += \
./Middlewares/modbus/ascii/mbascii.o 

C_DEPS += \
./Middlewares/modbus/ascii/mbascii.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/ascii/%.o: ../Middlewares/modbus/ascii/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


