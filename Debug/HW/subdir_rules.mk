################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
HW/comm.obj: ../HW/comm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/cc7/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/cc7/ccsv7/ccs_base/arm/include" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2/HW" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2/HW/driverlib/MSP432P4xx" --include_path="C:/cc7/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2" --include_path="C:/cc7/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="HW/comm.d" --obj_directory="HW" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

HW/register.obj: ../HW/register.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/cc7/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/cc7/ccsv7/ccs_base/arm/include" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2/HW" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2/HW/driverlib/MSP432P4xx" --include_path="C:/cc7/ccsv7/ccs_base/arm/include/CMSIS" --include_path="C:/Users/Joonatan/workspace_v7/PowerHourVer2" --include_path="C:/cc7/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="HW/register.d" --obj_directory="HW" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


