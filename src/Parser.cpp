#include <stdio.h>
#include <deque>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include <sg/Parser.h>

using namespace std;

Command* Parser::parseCommand(int argc, char *argv[]) {
	Command* cmd = new Command;
	cmd->action = EMBED;
	cmd->stenography = LSB1;
	cmd->encription = AES128;
	cmd->encriptionBlock = ECB;
	cmd->password = NULL;
	cmd->inputFile = loadFile("./res/secret.txt");
	cmd->hostFile = loadFile("./res/original.bmp");
	cmd->outputFilePath = "./res/troyanHorse.bmp";
	return cmd;
}

ifstream* Parser::loadFile(string path) {
	ifstream* file = new ifstream(path, ios::in | ios::binary | ios::ate);
	if (!file) {
		cerr << "Fallo el leer " << path << endl;
		throw "Fallo el leer el archivo";
	}
	return file;
}

