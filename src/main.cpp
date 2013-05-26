#include <stdio.h>
#include "Parser.h"
#include "stenography/Stenography.h"
#include <iostream>
#include <deque>

using namespace std;

int main (int argc, char *argv[]) {
	Parser* parser = new Parser();
	Command* command = parser->parseCommand(argc, argv);
	if (command == NULL) {
		printf("Erorr: %s", command->errorMsg->c_str());
		return 1;
	}
	
	Stenography* stenography;
	switch (command->stenography) {
		case LSB1:
			stenography = new Lsb1Stenography();
			break;
		case LSB4:
			break;
		case LSBE:
			break;
	}
	
	// Encript the file if needed
	
	// make a vec to stenograph (the image without the first 54bytes)
	 
	//Steanography execution
	if (command->action == EMBED) {
//		ans = stenography->embed(vec, vec);
	} else {
	//	ans = stenography->extract(vec);
	}
	
	//decrypt the file if needed
	
	//Save ans in file
	return 0;
}


