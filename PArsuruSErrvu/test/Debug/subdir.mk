################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DrawObject.cpp \
../Game.cpp \
../MoveableObject.cpp \
../Nave.cpp \
../Player.cpp \
../main.cpp \
../mainDeCliente.cpp 

OBJS += \
./DrawObject.o \
./Game.o \
./MoveableObject.o \
./Nave.o \
./Player.o \
./main.o \
./mainDeCliente.o 

CPP_DEPS += \
./DrawObject.d \
./Game.d \
./MoveableObject.d \
./Nave.d \
./Player.d \
./main.d \
./mainDeCliente.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -O0 -g3 -Wall -c -fmessage-length=0  -lSDL2 -lSDL2_image -lSDL_ttf  -std=c++11  -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


