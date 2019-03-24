################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/zzz.c 

OBJS += \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/zzz.o 

C_DEPS += \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/zzz.d 


# Each subdirectory must supply rules for building sources it contributes
test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/%.o: ../test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/src/subfolder/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace/soopc.test/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


