#include <stdio.h>
#include <deque>
#include <iostream>
#include <fstream>

#include "Parser.h"

/*
r  - open for reading
w  - open for writing (file need not exist)
a  - open for appending (file need not exist)
r+ - open for reading and writing, start at beginning
w+ - open for reading and writing (overwrite file)
a+ - open for reading and writing (append if file exists)
*/

using namespace std;

Command* Parser::parseCommand(int argc, char *argv[]) {
	Command* cmd = new Command;
	cmd->action = EMBED;
	cmd->stenography = LSB1;
	cmd->encription = AES128;
	cmd->encriptionBlock = ECB;
	cmd->password = NULL;
	cmd->inputFileDeque = loadFileToDeque("../res/secret.txt");
	for (unsigned int i = 0 ; i < cmd->inputFileDeque->size() ; i++) {
		cout << cmd->inputFileDeque->at(i);	
	}
	cout << endl;
	cmd->outputFilePath = "../res/troyanHorse.bmp";
	cmd->hostFileDeque = loadFileToDeque("../res/original.bmp");
	return cmd;
}

deque<char>* Parser::loadFileToDeque(string path) {
	ifstream file(path, ios::in | ios::binary | ios::ate);
	if (!file) {
		cerr << "Fallo el leer" << endl;
		throw "Fallo el leer el archivo";
	}
	long size = file.tellg();
	file.seekg(0);
	char* buffer = new char[size];
	file.read(buffer, size);
	deque<char> *vec = new deque<char>(buffer, buffer + size);
	return vec;
}
