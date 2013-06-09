#include <stdio.h>
#include <iostream>
#include <deque>
#include <sg/Parser.h>
#include <sg/stenography/Stenography.h>
#include <sg/encription/EncriptionStrategy.h>
#include <sg/stenography/BMPStenographier.h>

using namespace std;

int main (int argc, char *argv[]) {
	cout << argv[0] << endl;
	Parser* parser = new Parser();
	Command* command = parser->parseCommand(argc, argv);
	if (command == NULL) {
		cout << "Comando invalido. Ningun cambio fue relizado" << endl;
		return 1;
	}
	Stenography* stenography;
	switch (*command->stenography) {
		case LSB1:
			stenography = new LsbStenography(1);
			break;
		case LSB4:
			stenography = new LsbStenography(4);
			break;
		case LSBE:
			stenography = new LsbEStenography();
			break;
	}
	EncriptionStrategy* encription;
	const char * password = command->password.c_str();
	EncriptionBlockType* encriptionBlock = command->encriptionBlock;
	EncriptionType selectedEncription = command->encription == NULL ? NONE : *command->encription;
	switch(selectedEncription) {
		case AES128:
			encription = new Aes128EncriptionStrategy(password, encriptionBlock);
			break;
		case AES192:
			encription = new Aes192EncriptionStrategy(password, encriptionBlock);
			break;
		case AES256:
			encription = new Aes256EncriptionStrategy(password, encriptionBlock);
			break;
		case DES:
			encription = new DesEncriptionStrategy(password, encriptionBlock);
			break;
		case NONE:
		default:
			encription = NULL;
	}
	BMPStenographier stenographer;
	if (*command->action == EMBED) {
		stenographer.embed(command->hostFile, command->inputFile, command->outputFile, *stenography, encription);
	} else {
		stenographer.extract(command->hostFile, command->outputFile, *stenography, encription);
	}
	cout << "Programa finalizado correctamente" << endl;
	return 0;
}


