################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/vendor/ceedling/vendor/c_exception/lib/CException.c 

OBJS += \
./test/vendor/ceedling/vendor/c_exception/lib/CException.o 

C_DEPS += \
./test/vendor/ceedling/vendor/c_exception/lib/CException.d 


# Each subdirectory must supply rules for building sources it contributes
test/vendor/ceedling/vendor/c_exception/lib/%.o: ../test/vendor/ceedling/vendor/c_exception/lib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace/soopc.test/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


