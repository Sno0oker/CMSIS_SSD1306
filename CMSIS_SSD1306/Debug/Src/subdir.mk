################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/delay.c \
../Src/main.c \
../Src/spi.c \
../Src/ssd1306.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/delay.o \
./Src/main.o \
./Src/spi.o \
./Src/ssd1306.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/delay.d \
./Src/main.d \
./Src/spi.d \
./Src/ssd1306.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I"C:/Users/vital/STM32CubeIDE/workspace_1.8.0/CMSIS_SSD1306/Inc" -I"C:/Users/vital/STM32CubeIDE/workspace_1.8.0/CMSIS_SSD1306/CMSIS/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/delay.d ./Src/delay.o ./Src/main.d ./Src/main.o ./Src/spi.d ./Src/spi.o ./Src/ssd1306.d ./Src/ssd1306.o ./Src/syscalls.d ./Src/syscalls.o ./Src/sysmem.d ./Src/sysmem.o

.PHONY: clean-Src

