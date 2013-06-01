#pragma once

#include <string>

using namespace std;

typedef enum {
	EMBED, EXTRACT
} ActionType;

typedef enum {
	LSB1, LSB4, LSBE
} StenographyType;

typedef enum {
	AES128, AES192, AES256, DES
} EncriptionType;

typedef enum {
	ECB, CFB, OFB, CBC
} EncriptionBlockType;

typedef struct Command {
	ActionType action;
	StenographyType stenography;
	EncriptionType encription;
	EncriptionBlockType encriptionBlock;
	string* errorMsg;
	string* password;

	// Archivo a esconder (solo para embed action)
	// deque<char>* inputFileDeque;
	ifstream* inputFile;

	// Archivo de salida
	string outputFilePath;

	// Archivo portador de la imagen
	// deque<char>* hostFileDeque;
	ifstream* hostFile;
} Command;

class Parser {
	public:
		Command* parseCommand(int argc, char *argv[]);
	private:
		// deque<char>* loadFileToDeque(string path);
		ifstream* loadFile(string path);
};
