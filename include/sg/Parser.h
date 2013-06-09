#pragma once

#include <string>
#include <map>

using namespace std;

typedef enum {
	EMBED, EXTRACT
} ActionType;

typedef enum {
	LSB1, LSB4, LSBE
} StenographyType;

typedef enum {
	AES128, AES192, AES256, DES, NONE
} EncriptionType;

typedef enum {
	ECB, CFB, OFB, CBC
} EncriptionBlockType;

typedef struct Command {
	ActionType* action;
	StenographyType* stenography;
	EncriptionType* encription;
	EncriptionBlockType* encriptionBlock;

	string password;	// Password a utilizar para el algoritmo de encriptacion
	string inputFile;	// Archivo a esconder (solo para embed action)
	string outputFile;	// Archivo de salida
	string hostFile;	// Archivo portador de la imagen
} Command;

class Parser {
	public:
		Command* parseCommand(int argc, char *argv[]);
	private:
		void printUsage();
};
