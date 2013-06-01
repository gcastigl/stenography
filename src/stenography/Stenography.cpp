#include <sg/stenography/Stenography.h>
#include <sg/exception.h>
#include <fstream>
#include <iostream>
#include <array>

using namespace std;

vector<char>& Stenography::convertToArray(ifstream& file) {
	size_t size = file.tellg();
	file.seekg(0);
	char* buffer = new char[size];
	file.read(buffer, size);
	vector<char>* values = new vector<char>();
	for (size_t i = 0 ; i < size ; i++) {
		values->push_back(buffer[i]);
	}
	return *values;
}

void Stenography::embed(ifstream& host, ifstream& secret, ofstream& outfile) {
	if (!embedable(host, secret)) {
		throw new IllegalArgumentException("secret does not fit into host!!");
	}
	vector<char> secretArray = convertToArray(secret);
	vector<char> hostArray = convertToArray(host);
	u_int index = 55;
	cout << "Embedding bytes from secret to host" << endl;
	for (u_int i = 0; i < secretArray.size(); i++) {
		char hide = secretArray.at(i);
		embed(hide, hostArray, index);
	}
	// Fill buffer with remaining vales from host bytes
	outfile.write(hostArray.data(), hostArray.size());
	cout << "stenography saved written successfully" << endl;
}

void Stenography::extract(ifstream& host, ofstream& outfile) {
	//deque<char>* hostDeque = convertoToDeque(host);
	// ...
}
