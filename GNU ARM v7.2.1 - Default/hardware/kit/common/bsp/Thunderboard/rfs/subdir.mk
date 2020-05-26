################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hardware/kit/common/bsp/Thunderboard/rfs/rfs.c 

OBJS += \
./hardware/kit/common/bsp/Thunderboard/rfs/rfs.o 

C_DEPS += \
./hardware/kit/common/bsp/Thunderboard/rfs/rfs.d 


# Each subdirectory must supply rules for building sources it contributes
hardware/kit/common/bsp/Thunderboard/rfs/rfs.o: ../hardware/kit/common/bsp/Thunderboard/rfs/rfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DHAL_CONFIG=1' '-D__HEAP_SIZE=0xD00' '-D__STACK_SIZE=0x800' '-D__StackLimit=0x20000000' '-DEFR32MG12P332F1024GL125=1' -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/Device/SiliconLabs/EFR32MG12P/Include" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/Device/SiliconLabs/EFR32MG12P/Source" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/hardware/kit/common/bsp" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/CMSIS/Include" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/Device/SiliconLabs/EFR32MG12P/Source/GCC" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emlib/src" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/dmadrv/src" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/hardware/kit/common/drivers" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/service/sleeptimer/src" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/sleep/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/dmadrv/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/app/bluetooth/common/util" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/protocol/bluetooth/ble_stack/inc/soc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/service/sleeptimer/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/hardware/kit/common/halconfig" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/protocol/bluetooth/ble_stack/inc/common" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/uartdrv/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/gpiointerrupt/src" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/common/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/radio/rail_lib/chip/efr32/efr32xg1x" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/hardware/kit/EFR32MG12_BRD4166A/config" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/service/sleeptimer/config" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/halconfig/inc/hal-config" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/emdrv/sleep/src" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog" -I"/Users/clfilho/SimplicityStudio/March20/TBS2_ALSLog/platform/bootloader" -O0 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -MMD -MP -MF"hardware/kit/common/bsp/Thunderboard/rfs/rfs.d" -MT"hardware/kit/common/bsp/Thunderboard/rfs/rfs.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


