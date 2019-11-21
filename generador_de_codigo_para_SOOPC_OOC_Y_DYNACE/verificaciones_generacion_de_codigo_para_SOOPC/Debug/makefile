################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src-gen/Aplicacion/subdir.mk
-include src-gen/subdir.mk
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
all: soopc.test

dependents:
	-cd /home/marino/workspace/soopc.test/Release && $(MAKE) all

# Tool invocations
soopc.test: $(OBJS) $(USER_OBJS) /home/marino/workspace/soopc.test/Release/soopc.test
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "soopc.test" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) soopc.test
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/marino/workspace/soopc.test/Release/soopc.test:

-include ../makefile.targets
