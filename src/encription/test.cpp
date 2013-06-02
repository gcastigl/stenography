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
	char * data = "Secret";
	vector<char>* in = new vector<char>();
	for(int i = 0; i < strlen(data); i++){
		in->push_back((char)(data[i]));
	}
	printVec(*in);
	vector<char> out = e->encript(CBC, (unsigned char *)"0123456789123456", *in);
	printVec(out);
	vector<char> decripted = e->decript(CBC, (unsigned char *)"0123456789123456", out);
	printVec(decripted);
}

void printVec(vector<char>& vec){
	printf("--%d--", vec.size());
	for(int i= 0; i < vec.size(); i++){
		printf("%c", vec.data()[i]);
	}
	printf("--\n");
}

