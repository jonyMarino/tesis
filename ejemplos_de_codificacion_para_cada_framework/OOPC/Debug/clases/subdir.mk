################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../clases/Child.c \
../clases/Parent.c \
../clases/Parent2.c 

OBJS += \
./clases/Child.o \
./clases/Parent.o \
./clases/Parent2.o 

C_DEPS += \
./clases/Child.d \
./clases/Parent.d \
./clases/Parent2.d 


# Each subdirectory must supply rules for building sources it contributes
clases/%.o: ../clases/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I.. -I../clases -I"/home/marino/workspace/OOPC/ooc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


