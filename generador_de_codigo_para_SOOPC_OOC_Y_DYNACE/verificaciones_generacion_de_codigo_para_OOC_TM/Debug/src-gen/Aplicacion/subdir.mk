################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src-gen/Aplicacion/Aplicacion.c \
../src-gen/Aplicacion/Child.c \
../src-gen/Aplicacion/Class1.c \
../src-gen/Aplicacion/Countable.c \
../src-gen/Aplicacion/GrandChild.c \
../src-gen/Aplicacion/Parent.c \
../src-gen/Aplicacion/Serializable.c 

OBJS += \
./src-gen/Aplicacion/Aplicacion.o \
./src-gen/Aplicacion/Child.o \
./src-gen/Aplicacion/Class1.o \
./src-gen/Aplicacion/Countable.o \
./src-gen/Aplicacion/GrandChild.o \
./src-gen/Aplicacion/Parent.o \
./src-gen/Aplicacion/Serializable.o 

C_DEPS += \
./src-gen/Aplicacion/Aplicacion.d \
./src-gen/Aplicacion/Child.d \
./src-gen/Aplicacion/Class1.d \
./src-gen/Aplicacion/Countable.d \
./src-gen/Aplicacion/GrandChild.d \
./src-gen/Aplicacion/Parent.d \
./src-gen/Aplicacion/Serializable.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/Aplicacion/%.o: ../src-gen/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -I"/home/marino/workspace/OocDemo/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


