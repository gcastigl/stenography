################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/encription/Aes128EncriptionStrategy.cpp \
../src/encription/Aes192EncriptionStrategy.cpp \
../src/encription/Aes256EncriptionStrategy.cpp \
../src/encription/DesEncriptionStrategy.cpp \
../src/encription/testEnc.cpp 

OBJS += \
./src/encription/Aes128EncriptionStrategy.o \
./src/encription/Aes192EncriptionStrategy.o \
./src/encription/Aes256EncriptionStrategy.o \
./src/encription/DesEncriptionStrategy.o \
./src/encription/testEnc.o 

CPP_DEPS += \
./src/encription/Aes128EncriptionStrategy.d \
./src/encription/Aes192EncriptionStrategy.d \
./src/encription/Aes256EncriptionStrategy.d \
./src/encription/DesEncriptionStrategy.d \
./src/encription/testEnc.d 


# Each subdirectory must supply rules for building sources it contributes
src/encription/%.o: ../src/encription/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/gcastigl/workspace/stenography/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


