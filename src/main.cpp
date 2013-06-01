#include <stdio.h>
#include <iostream>
#include <deque>
#include <sg/Parser.h>
#include <sg/stenography/Stenography.h>
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
			break;
	}
	
	BMPStenographier stenographier;
	//Steanography execution
	if (command.action == EMBED) {
		stenographier.embed(command.hostFile, command.inputFile, command.outputFile, *stenography, nullptr);
	} else {
	//	ans = stenography->extract(vec);
	}
	
	cout << "Program succesfully finished" << endl;
	return 0;
}


