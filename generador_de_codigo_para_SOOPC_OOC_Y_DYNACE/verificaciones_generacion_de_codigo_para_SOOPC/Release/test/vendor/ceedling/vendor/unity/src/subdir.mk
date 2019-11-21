################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/vendor/ceedling/vendor/unity/src/unity.c 

OBJS += \
./test/vendor/ceedling/vendor/unity/src/unity.o 

C_DEPS += \
./test/vendor/ceedling/vendor/unity/src/unity.d 


# Each subdirectory must supply rules for building sources it contributes
test/vendor/ceedling/vendor/unity/src/%.o: ../test/vendor/ceedling/vendor/unity/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


