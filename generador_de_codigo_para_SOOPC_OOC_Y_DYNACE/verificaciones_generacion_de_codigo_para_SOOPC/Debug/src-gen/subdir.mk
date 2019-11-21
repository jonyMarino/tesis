################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src-gen/.c \
../src-gen/src-gen.c 

OBJS += \
./src-gen/src-gen.o 

C_DEPS += \
./src-gen.d \
./src-gen/src-gen.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/%.o: ../src-gen/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace/soopc.test/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


