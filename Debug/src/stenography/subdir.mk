################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/stenography/BMPStenographier.cpp \
../src/stenography/LsbEStenography.cpp \
../src/stenography/LsbStenography.cpp \
../src/stenography/Stenography.cpp 

OBJS += \
./src/stenography/BMPStenographier.o \
./src/stenography/LsbEStenography.o \
./src/stenography/LsbStenography.o \
./src/stenography/Stenography.o 

CPP_DEPS += \
./src/stenography/BMPStenographier.d \
./src/stenography/LsbEStenography.d \
./src/stenography/LsbStenography.d \
./src/stenography/Stenography.d 


# Each subdirectory must supply rules for building sources it contributes
src/stenography/%.o: ../src/stenography/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/home/gcastigl/workspace/stenography/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


