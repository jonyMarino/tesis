################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src-gen/Aplicacion/Aplicacion.c \
../src-gen/Aplicacion/Child.c \
../src-gen/Aplicacion/GrandChild.c \
../src-gen/Aplicacion/Parent.c 

OBJS += \
./src-gen/Aplicacion/Aplicacion.o \
./src-gen/Aplicacion/Child.o \
./src-gen/Aplicacion/GrandChild.o \
./src-gen/Aplicacion/Parent.o 

C_DEPS += \
./src-gen/Aplicacion/Aplicacion.d \
./src-gen/Aplicacion/Child.d \
./src-gen/Aplicacion/GrandChild.d \
./src-gen/Aplicacion/Parent.d 


# Each subdirectory must supply rules for building sources it contributes
src-gen/Aplicacion/%.o: ../src-gen/Aplicacion/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace_tesis/tesis/generador_de_codigo_para_SOOPC_OOC_Y_DYNACE/verificaciones_generacion_de_codigo_para_SOOPC/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


