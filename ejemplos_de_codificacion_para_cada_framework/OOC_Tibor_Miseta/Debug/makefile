################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src-gen/Aplicacion/subdir.mk
-include src-gen/subdir.mk
-include ooc/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: OOC-TM

# Tool invocations
OOC-TM: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc -L"/home/marino/workspace/tesis/ejemplos_de_codificacion_para_cada_framework/OOC_Tibor_Miseta" -o "OOC-TM" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) OOC-TM
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
