################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ooc/exception.c \
../ooc/list.c \
../ooc/ooc.c \
../ooc/refcounted.c \
../ooc/signal.c \
../ooc/testcase.c \
../ooc/vector.c 

OBJS += \
./ooc/exception.o \
./ooc/list.o \
./ooc/ooc.o \
./ooc/refcounted.o \
./ooc/signal.o \
./ooc/testcase.o \
./ooc/vector.o 

C_DEPS += \
./ooc/exception.d \
./ooc/list.d \
./ooc/ooc.d \
./ooc/refcounted.d \
./ooc/signal.d \
./ooc/testcase.d \
./ooc/vector.d 


# Each subdirectory must supply rules for building sources it contributes
ooc/%.o: ../ooc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c99 -I"/home/marino/workspace/tesis/ejemplos_de_codificacion_para_cada_framework/OOC_Tibor_Miseta/src-gen" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


