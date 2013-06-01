#include <sg/stenography/Stenography.h>
#include <sg/exception.h>
#include <fstream>
#include <iostream>
#include <deque>

deque<char>* Stenography::convertoToDeque(ifstream& file) {
	long size = file.tellg();
	file.seekg(0);
	char* buffer = new char[size];
	file.read(buffer, size);
	return new deque<char>(buffer, buffer + size);
}

void Stenography::embed(ifstream& host, ifstream& secret, ofstream& outfile) {
	if (!embedable(host, secret)) {
		throw new IllegalArgumentException("secret does not fit into host!!");
	}
	deque<char>* secretDeque = convertoToDeque(secret);
	deque<char>* hostDeque = convertoToDeque(host);
	cout << "Secret length: " << secretDeque->size() << endl;
	cout << "Host length: " << hostDeque->size() << endl;
	size_t totalSize = hostDeque->size();
	char* stenographied = new char[totalSize];
	u_int index = totalSize - 1;
	cout << "Embedding bytes from secret to host" << endl;
	for (u_int i = 0; i < secretDeque->size(); i++) {
		char hide = secretDeque->at(i);
		embed(hide, hostDeque, stenographied, index);
	}
	// Fill buffer with remaining vales from host bytes
	long remaining = index;
	cout << "Remaining bytes to be written: " << remaining << endl;
	do {
		stenographied[remaining] = hostDeque->at(remaining);
		remaining--;
	} while (remaining >= 0);
	outfile.write(stenographied, totalSize);
	cout << "stenography saved written successfully" << endl;
}

void Stenography::extract(ifstream& host, ofstream& outfile) {
	deque<char>* hostDeque = convertoToDeque(host);
	// ...
}
