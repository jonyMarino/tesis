################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/test/test_gen_child.c \
../test/test/test_gen_grandchild.c \
../test/test/test_gen_parent.c 

OBJS += \
./test/test/test_gen_child.o \
./test/test/test_gen_grandchild.o \
./test/test/test_gen_parent.o 

C_DEPS += \
./test/test/test_gen_child.d \
./test/test/test_gen_grandchild.d \
./test/test/test_gen_parent.d 


# Each subdirectory must supply rules for building sources it contributes
test/test/%.o: ../test/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


