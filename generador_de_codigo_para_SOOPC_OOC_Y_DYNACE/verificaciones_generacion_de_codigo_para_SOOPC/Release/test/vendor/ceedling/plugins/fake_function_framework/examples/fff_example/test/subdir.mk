################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_event_processor.c \
../test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_foo.c 

OBJS += \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_event_processor.o \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_foo.o 

C_DEPS += \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_event_processor.d \
./test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/test_foo.d 


# Each subdirectory must supply rules for building sources it contributes
test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/%.o: ../test/vendor/ceedling/plugins/fake_function_framework/examples/fff_example/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


