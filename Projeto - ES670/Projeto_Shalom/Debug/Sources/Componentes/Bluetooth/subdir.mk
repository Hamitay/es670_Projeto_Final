################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Componentes/Bluetooth/uart1.c 

OBJS += \
./Sources/Componentes/Bluetooth/uart1.o 

C_DEPS += \
./Sources/Componentes/Bluetooth/uart1.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Componentes/Bluetooth/%.o: ../Sources/Componentes/Bluetooth/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -I"D:\Freescale\KSDK_1.2.0\platform\drivers\inc" -I"D:\Freescale\KSDK_1.2.0\platform\utilities\inc" -I"D:\Freescale\KSDK_1.2.0\platform\hal\inc" -I"D:\Freescale\KSDK_1.2.0\platform\system\inc" -I"D:\Freescale\KSDK_1.2.0\platform\osa\inc" -I"D:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"D:\Freescale\KSDK_1.2.0/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


