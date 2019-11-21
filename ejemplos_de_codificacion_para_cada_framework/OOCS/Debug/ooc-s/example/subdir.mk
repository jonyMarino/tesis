################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc-s/example/interface_example.c \
../ooc-s/example/main.c \
../ooc-s/example/parent.c 

OBJS += \
./ooc-s/example/interface_example.o \
./ooc-s/example/main.o \
./ooc-s/example/parent.o 

C_DEPS += \
./ooc-s/example/interface_example.d \
./ooc-s/example/main.d \
./ooc-s/example/parent.d 


# Each subdirectory must supply rules for building sources it contributes
ooc-s/example/%.o: ../ooc-s/example/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace_tesis/tesis/ejemplos_de_codificacion_para_cada_framework/OOCS/ooc-s" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


