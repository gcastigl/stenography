#!/bin/bash -e

cd ./bin
rm -f stegobmp

cd ../src
g++ -Wall -std=c++11 -o ../bin/stegobmp \
	./main.cpp \
	./Parser.cpp \
	./stenography/Lsb1Stenography.cpp 
	# ./encription/Aes128EncriptionStrategy.cpp \

../bin/stegobmp
