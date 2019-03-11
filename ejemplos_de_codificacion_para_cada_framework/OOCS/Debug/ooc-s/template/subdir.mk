################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc-s/template/interface.c \
../ooc-s/template/type.c 

OBJS += \
./ooc-s/template/interface.o \
./ooc-s/template/type.o 

C_DEPS += \
./ooc-s/template/interface.d \
./ooc-s/template/type.d 


# Each subdirectory must supply rules for building sources it contributes
ooc-s/template/%.o: ../ooc-s/template/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


