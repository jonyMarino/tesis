################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/build/test/runners/test_gen_child_runner.c \
../test/build/test/runners/test_gen_grandchild_runner.c \
../test/build/test/runners/test_gen_parent_runner.c 

OBJS += \
./test/build/test/runners/test_gen_child_runner.o \
./test/build/test/runners/test_gen_grandchild_runner.o \
./test/build/test/runners/test_gen_parent_runner.o 

C_DEPS += \
./test/build/test/runners/test_gen_child_runner.d \
./test/build/test/runners/test_gen_grandchild_runner.d \
./test/build/test/runners/test_gen_parent_runner.d 


# Each subdirectory must supply rules for building sources it contributes
test/build/test/runners/%.o: ../test/build/test/runners/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


