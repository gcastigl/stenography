#include <sg/stenography/Stenography.h>
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
