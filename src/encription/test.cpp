/*
 * test.cpp
 *
 *  Created on: Jun 1, 2013
 *      Author: gcastigl
 */
#include <sg/encription/Encription.h>
#include <string.h>
#include <stdio.h>

void printVec(vector<char>& vec);

int main_() {
	Aes128EncriptionStrategy* e = new Aes128EncriptionStrategy();
	char * data = "01234567893456";
	vector<char>* in = new vector<char>();
	for(int i = 0; i < strlen(data); i++){
		in->push_back((char)(data[i]));
	}
	printVec(*in);
	vector<char> out = e->encript(CBC, (unsigned char *)"myPassword", *in);
	printVec(out);
	fflush(stdout);
	vector<char> decripted = e->decript(CBC, (unsigned char *)"myPassword", out);
	printVec(decripted);
	fflush(stdout);
}

void printVec(vector<char>& vec){
	printf("--%d--", vec.size());
	for(int i= 0; i < vec.size(); i++){
		printf("%c", vec.data()[i]);
	}
	printf("--\n");
}

