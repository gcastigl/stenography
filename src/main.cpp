#include <stdio.h>
#include <iostream>
#include <deque>
#include <sg/Parser.h>
#include <sg/stenography/Stenography.h>

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
			break;
	}
	
	// Encript the file if needed
	
	// make a vec to stenograph (the image without the first 54bytes)
	 
	//Steanography execution
	if (command.action == EMBED) {
		stenography->embed(*command.hostFile, *command.inputFile, *command.outputFile);
	} else {
	//	ans = stenography->extract(vec);
	}
	//decrypt the file if needed
	
	//Save ans in file
	command.outputFile->close();
	cout << "Program succesfully finished" << endl;
	return 0;
}


