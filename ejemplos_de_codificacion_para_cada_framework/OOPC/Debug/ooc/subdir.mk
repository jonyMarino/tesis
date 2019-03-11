################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc/exception.c \
../ooc/ooc.c \
../ooc/oodebug.c 

OBJS += \
./ooc/exception.o \
./ooc/ooc.o \
./ooc/oodebug.o 

C_DEPS += \
./ooc/exception.d \
./ooc/ooc.d \
./ooc/oodebug.d 


# Each subdirectory must supply rules for building sources it contributes
ooc/%.o: ../ooc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I.. -I../clases -I"/home/marino/workspace/OOPC/ooc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


