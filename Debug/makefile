################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./BME280/I2C.obj" \
"./BME280/bme280.obj" \
"./BME280/bme280_support.obj" \
"./ClockSystem/ClockSystem.obj" \
"./ESP8266/esp8266.obj" \
"./ILI9341/UserInterface.obj" \
"./ILI9341/hal.obj" \
"./ILI9341/ili9341.obj" \
"./PrintfOverride/PrintfOverride.obj" \
"./RTC/RTC.obj" \
"./UART_Terminal/UART_Terminal.obj" \
"../driverlib_empty_project_ccs.cmd" \
"C:/ti/msp/MSP432Ware_3_50_00_02/driverlib/driverlib/MSP432P4xx/ccs/msp432p4xx_driverlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include BME280/subdir_vars.mk
-include ClockSystem/subdir_vars.mk
-include ESP8266/subdir_vars.mk
-include ILI9341/subdir_vars.mk
-include PrintfOverride/subdir_vars.mk
-include RTC/subdir_vars.mk
-include UART_Terminal/subdir_vars.mk
-include subdir_rules.mk
-include BME280/subdir_rules.mk
-include ClockSystem/subdir_rules.mk
-include ESP8266/subdir_rules.mk
-include ILI9341/subdir_rules.mk
-include PrintfOverride/subdir_rules.mk
-include RTC/subdir_rules.mk
-include UART_Terminal/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
WiFi_Interface.out \

EXE_OUTPUTS__QUOTED += \
"WiFi_Interface.out" \

BIN_OUTPUTS += \
WiFi_Interface.bin \

BIN_OUTPUTS__QUOTED += \
"WiFi_Interface.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "WiFi_Interface.out"

# Tool invocations
WiFi_Interface.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=TARGET_IS_MSP432P4XX --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number -z -m"WiFi_Interface.map" --stack_size=512 -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/lib" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="WiFi_Interface_linkInfo.xml" --rom_model -o "WiFi_Interface.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

WiFi_Interface.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armhex"  -o "WiFi_Interface.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "BME280\I2C.obj" "BME280\bme280.obj" "BME280\bme280_support.obj" "ClockSystem\ClockSystem.obj" "ESP8266\esp8266.obj" "ILI9341\UserInterface.obj" "ILI9341\hal.obj" "ILI9341\ili9341.obj" "PrintfOverride\PrintfOverride.obj" "RTC\RTC.obj" "UART_Terminal\UART_Terminal.obj" 
	-$(RM) "main.d" "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "BME280\I2C.d" "BME280\bme280.d" "BME280\bme280_support.d" "ClockSystem\ClockSystem.d" "ESP8266\esp8266.d" "ILI9341\UserInterface.d" "ILI9341\hal.d" "ILI9341\ili9341.d" "PrintfOverride\PrintfOverride.d" "RTC\RTC.d" "UART_Terminal\UART_Terminal.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccsv7/utils/tiobj2bin/tiobj2bin WiFi_Interface.out WiFi_Interface.bin C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armofd C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.7.LTS/bin/armhex C:/ti/ccsv7/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

