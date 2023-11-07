################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/InitDevice.c \
../src/Interrupts.c \
../src/adc.c \
../src/button.c \
../src/gen.c \
../src/main.c \
../src/sbus.c 

OBJS += \
./src/InitDevice.OBJ \
./src/Interrupts.OBJ \
./src/adc.OBJ \
./src/button.OBJ \
./src/gen.OBJ \
./src/main.OBJ \
./src/sbus.OBJ 


# Each subdirectory must supply rules for building sources it contributes
src/%.OBJ: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Keil 8051 Compiler'
	C51 "@$(patsubst %.OBJ,%.__i,$@)" || $(RC)
	@echo 'Finished building: $<'
	@echo ' '

src/InitDevice.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/InitDevice.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/Interrupts.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/sbus.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/adc.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/adc.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/button.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/button.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/gen.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/button.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/adc.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/main.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/InitDevice.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/sbus.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/button.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/adc.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h

src/sbus.OBJ: C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/sbus.h C:/src/Tennp/Git/SBUS_PWM_PWR/Firmware/src/main.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdint.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Register_Enums.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/EFM8BB51/inc/SI_EFM8BB51_Defs.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/si_toolchain.h C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/8051/v4.2.3/Device/shared/si8051Base/stdbool.h


