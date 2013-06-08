#include <stdio.h>

#include <sg/Parser.h>

using namespace std;

Command* Parser::parseCommand(int argc, char *argv[]) {
	Command* cmd = new Command;
	cmd->action = EXTRACT;
	cmd->stenography = LSB4;
	cmd->encription = AES256;
	cmd->encriptionBlock = OFB;
	cmd->password = "secreto";
	cmd->inputFile = "./res/secret.txt";
	cmd->hostFile = "./res/th.bmp";
	cmd->outputFile = "./res/result";
	//cmd->hostFile = "./res/testPampero/sherlock4aes256ofb.bmp";
	//cmd->outputFile = "./res/testPampero/result";
	return cmd;
}



