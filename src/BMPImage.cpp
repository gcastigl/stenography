#include <stdio.h>

#include <string>
#include <iostream>
#include <fstream>
#include <array>
#include <vector>

#include "BMPImage.h"

using namespace std;

BMPImage::BMPImage(string filePath) {
	this->filePath = filePath;
}

// Metodo que se encarga de embeber el archivo en esta imagen BMP
// fileToEmbed: path del archivo que se quiere embeber.
// destFile: path del archivo destino.
// bits: cantidad de bits menos significativos que seran reemplazados por compenente por pixel.
void BMPImage::embedFile(string fileToEmbed, string destFile, int bits) {
	ifstream file(filePath, ios::in | ios::binary | ios::ate);
        size = file.tellg();
	file.seekg(0);
	if (bits != 1 && bits != 4) {
		//Printea a stderr
		cerr << "Invalid bit amount: " << bits << "\n";
		return;
	} 
	ofstream outputFile(destFile, ios::out | ios::binary);
	if (!outputFile) {
		cerr << "Error creating destination file\n";
		return;
	}
	ifstream inputFile(fileToEmbed, ios::in | ios::binary | ios::ate);
	int embedFileSize = inputFile.tellg();
	inputFile.seekg(0, ios::beg);
	if (!inputFile) {
		cerr << "Error opening file to embed\n";
		return;
	}
	if (bits * size / 8 < embedFileSize) {
		cerr << "The file you want to embed doesn't fit inside the image\n";
		return;
	}
	// Para un buffer de entrada, solo se podran guardar hasta bits*BUFFER_SIZE/8 bytes
	int inputBufferSize = bits * BUFFER_SIZE / 8;
	char * fileInputBuffer = new char[inputBufferSize], * imageInputBuffer = new char[BUFFER_SIZE], * outputBuffer = new char[BUFFER_SIZE];
	if (!file.read(outputBuffer, HEADER_SIZE)) {
		cerr << "Error while reading image\n";
		return;
	}
	outputFile.write(outputBuffer, HEADER_SIZE);
	do {
		inputFile.read(fileInputBuffer, inputBufferSize);
		if (inputFile.bad()) {
			cerr << "Error reading input file\n";
			return;
		}
		int bytesToWrite = BUFFER_SIZE;
		if (!file.read(imageInputBuffer, BUFFER_SIZE)) {
			if (file.eof()) {
				bytesToWrite = file.gcount();
			} else {
				cerr << "Error embeding file into image\n";
				return;
			}
		}
		maskBytes(imageInputBuffer, fileInputBuffer, bits, bytesToWrite, outputBuffer); 
		if (!outputFile.write(outputBuffer, bytesToWrite)) {
			cerr << "An error occurred while writing the file\n";
			return;
		}
	} while(!inputFile.eof());
	//Terminar de rellenar con el resto de la imagen, si sobro
	while (!file.eof()) {
		int bytesToWrite = BUFFER_SIZE;
		if (!file.read(outputBuffer, BUFFER_SIZE)) {
			if (file.eof()) {
				bytesToWrite = file.gcount();
			} else {
				cerr << "Error embeding file into image\n";
				return;
			}
		}
		outputFile.write(outputBuffer, bytesToWrite);
	}
	long pos = outputFile.tellp();
	file.close();
	outputFile.close();
	inputFile.close();
	
}

void BMPImage::maskBytes(const char * originalBytes, const char * bytesToEmbed, int bits, int bytesToWrite, char * output) {
	for (int i = 0, j = 0 ; j < bytesToWrite ; i++) {
		char byteToEmbed = bytesToEmbed[i];
		for (int bit = 0 ; bit < 8 ; bit += bits, j++, byteToEmbed <<= bits) {
			output[j] = originalBytes[j] & (-1 << bits) | ((unsigned char)(byteToEmbed & (-1 << (8-bits)))) >> (8-bits);
		}
	}
}
