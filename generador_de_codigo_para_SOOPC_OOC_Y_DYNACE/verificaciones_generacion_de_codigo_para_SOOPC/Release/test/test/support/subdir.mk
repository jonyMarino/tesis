################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/test/support/asprintf.c 

OBJS += \
./test/test/support/asprintf.o 

C_DEPS += \
./test/test/support/asprintf.d 


# Each subdirectory must supply rules for building sources it contributes
test/test/support/%.o: ../test/test/support/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace/SoopcDemo/src-gen" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


