#include <stdio.h>
#include <iostream>
#include <deque>
#include <sg/Parser.h>
#include <sg/stenography/Stenography.h>
#include <sg/encription/EncriptionStrategy.h>
#include <sg/stenography/BMPStenographier.h>

using namespace std;

int main (int argc, char *argv[]) {
	printf("Sistema de encriptacion por estenografia v1.0\n");
	Parser* parser = new Parser();
	Command& command = *parser->parseCommand(argc, argv);
	if (command.errorMsg != NULL) {
		printf("Error: %s", command.errorMsg->c_str());
		return 1;
	}
	
	Stenography* stenography;
	switch (command.stenography) {
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
	ICrypto* encription;
	switch(command.encription){
		case AES128:
			encription = new Aes128EncriptionStrategy(command.password);
			break;
		case AES192:
			encription = new Aes192EncriptionStrategy(command.password);
			break;
		case AES256:
			encription = new Aes256EncriptionStrategy(command.password);
			break;
		case DES:
			encription = new DesEncriptionStrategy(command.password);
			break;
	}

	BMPStenographier stenographer;
	//Steanography execution
	if (command.action == EMBED) {
		stenographer.embed(command.hostFile, command.inputFile, command.outputFile, *stenography, encription, command.encriptionBlock);
	} else {
		stenographer.extract(command.hostFile, command.outputFile, *stenography, encription, command.encriptionBlock);
	}
	
	cout << "Program succesfully finished" << endl;
	return 0;
}


