################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/modbus/functions/mbfunccoils.c \
../Middlewares/modbus/functions/mbfuncdiag.c \
../Middlewares/modbus/functions/mbfuncdisc.c \
../Middlewares/modbus/functions/mbfuncholding.c \
../Middlewares/modbus/functions/mbfuncinput.c \
../Middlewares/modbus/functions/mbfuncother.c \
../Middlewares/modbus/functions/mbutils.c 

OBJS += \
./Middlewares/modbus/functions/mbfunccoils.o \
./Middlewares/modbus/functions/mbfuncdiag.o \
./Middlewares/modbus/functions/mbfuncdisc.o \
./Middlewares/modbus/functions/mbfuncholding.o \
./Middlewares/modbus/functions/mbfuncinput.o \
./Middlewares/modbus/functions/mbfuncother.o \
./Middlewares/modbus/functions/mbutils.o 

C_DEPS += \
./Middlewares/modbus/functions/mbfunccoils.d \
./Middlewares/modbus/functions/mbfuncdiag.d \
./Middlewares/modbus/functions/mbfuncdisc.d \
./Middlewares/modbus/functions/mbfuncholding.d \
./Middlewares/modbus/functions/mbfuncinput.d \
./Middlewares/modbus/functions/mbfuncother.d \
./Middlewares/modbus/functions/mbutils.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/modbus/functions/%.o: ../Middlewares/modbus/functions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"../Sources" -I"../Includes" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


