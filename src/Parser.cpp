#include <stdio.h>

#include <sg/Parser.h>

using namespace std;

Command* Parser::parseCommand(int argc, char *argv[]) {
	Command* cmd = new Command;
	cmd->action = EXTRACT;
	cmd->stenography = LSB1;
	cmd->encription = AES128;
	cmd->encriptionBlock = CBC;
	cmd->password = "jorgeMataNinios";
	cmd->inputFile = "./res/secret.txt";
	cmd->hostFile = "./res/troyanHorse.bmp";
	cmd->outputFile = "./res/result";
	return cmd;
}



