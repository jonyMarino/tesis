################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/build/test/preprocess/includes/test_gen_child.c \
../test/build/test/preprocess/includes/test_gen_grandchild.c \
../test/build/test/preprocess/includes/test_gen_parent.c 

OBJS += \
./test/build/test/preprocess/includes/test_gen_child.o \
./test/build/test/preprocess/includes/test_gen_grandchild.o \
./test/build/test/preprocess/includes/test_gen_parent.o 

C_DEPS += \
./test/build/test/preprocess/includes/test_gen_child.d \
./test/build/test/preprocess/includes/test_gen_grandchild.d \
./test/build/test/preprocess/includes/test_gen_parent.d 


# Each subdirectory must supply rules for building sources it contributes
test/build/test/preprocess/includes/%.o: ../test/build/test/preprocess/includes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


