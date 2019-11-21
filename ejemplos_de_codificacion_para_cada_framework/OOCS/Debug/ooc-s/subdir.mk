################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc-s/autorelease.c \
../ooc-s/clonable.c \
../ooc-s/comparable.c \
../ooc-s/copiable.c \
../ooc-s/object.c 

OBJS += \
./ooc-s/autorelease.o \
./ooc-s/clonable.o \
./ooc-s/comparable.o \
./ooc-s/copiable.o \
./ooc-s/object.o 

C_DEPS += \
./ooc-s/autorelease.d \
./ooc-s/clonable.d \
./ooc-s/comparable.d \
./ooc-s/copiable.d \
./ooc-s/object.d 


# Each subdirectory must supply rules for building sources it contributes
ooc-s/%.o: ../ooc-s/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/marino/workspace_tesis/tesis/ejemplos_de_codificacion_para_cada_framework/OOCS/ooc-s" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


