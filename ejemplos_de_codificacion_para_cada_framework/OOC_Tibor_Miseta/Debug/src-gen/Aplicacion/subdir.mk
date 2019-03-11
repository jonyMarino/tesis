################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src-gen/Aplicacion/Aplicacion.c \
../src-gen/Aplicacion/MyInterface.c \
../src-gen/Aplicacion/MyMixin.c \
../src-gen/Aplicacion/Parent.c 

OBJS += \
./src-gen/Aplicacion/Aplicacion.o \
./src-gen/Aplicacion/MyInterface.o \
./src-gen/Aplicacion/MyMixin.o \
./src-gen/Aplicacion/Parent.o 

C_DEPS += \
./src-gen/Aplicacion/Aplicacion.d \
./src-gen/Aplicacion/MyInterface.d \
./src-gen/Aplicacion/MyMixin.d \
./src-gen/Aplicacion/Parent.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/Aplicacion/%.o: ../src-gen/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -I"/home/marino/workspace/tesis/ejemplos_de_codificacion_para_cada_framework/OOC_Tibor_Miseta/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


