################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/001led_toggle.c 

OBJS += \
./Src/001led_toggle.o 

C_DEPS += \
./Src/001led_toggle.d 


# Each subdirectory must supply rules for building sources it contributes
Src/001led_toggle.o: ../Src/001led_toggle.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DSTM32F446RETx -DDEBUG -DNUCLEO_F446RE -c -I../Inc -I"N:/stm/stm32/stm32f4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/001led_toggle.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

