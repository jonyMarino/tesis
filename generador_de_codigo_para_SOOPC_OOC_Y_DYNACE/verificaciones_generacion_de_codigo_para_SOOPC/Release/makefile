################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include test/vendor/ceedling/vendor/unity/src/subdir.mk
-include test/vendor/ceedling/vendor/cmock/src/subdir.mk
-include test/vendor/ceedling/vendor/c_exception/lib/subdir.mk
-include test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/subdir.mk
-include test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/subdir.mk
-include test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subdir.mk
-include test/test/subdir.mk
-include test/build/test/runners/subdir.mk
-include test/build/test/preprocess/includes/subdir.mk
-include test/build/test/preprocess/files/subdir.mk
-include test/build/test/out/subdir.mk
-include test/build/test/cache/subdir.mk
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

# Tool invocations
soopc.test: $(OBJS) $(USER_OBJS)
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

-include ../makefile.targets
