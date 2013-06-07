#include <sg/stenography/BMPStenographier.h>
#include <sg/stenography/Stenography.h>
#include <sg/encription/EncriptionStrategy.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <string.h>

using namespace std;

void BMPStenographier::embed(string host, string secret, string output,
		Stenography& stenographer, ICrypto* encriptionStrategy, EncriptionBlockType mode) {
	ifstream& hostFile = *loadFile(host);
	ifstream& secretFile = *loadFile(secret);
	char* headerBuffer = new char[HEADER_SIZE];
	hostFile.read(headerBuffer, HEADER_SIZE);
	ofstream& outputFile = *(new ofstream(output, ios::binary));
	outputFile.write(headerBuffer, HEADER_SIZE);
	vector<char> secretData = convertToArray(secretFile);
	vector<char>* secretVector = &prepareVector(secretData, secret);

	if (encriptionStrategy != NULL) {
		*secretVector = encriptionStrategy->encript(mode, *secretVector);
		pushElement(*secretVector, secretVector->size());
	}

	stenographer.embed(convertToArray(hostFile), *secretVector, outputFile);
	hostFile.close();
	secretFile.close();
	outputFile.close();
}

void BMPStenographier::extract(string host, string output,
		Stenography& stenographer, ICrypto* encriptionStrategy, EncriptionBlockType mode) {
	ifstream& hostFile = *loadFile(host);
	hostFile.seekg(HEADER_SIZE);
	deque<char>& outputDeque = stenographer.extract(convertToArray(hostFile));
	int size;
	popElement(outputDeque, &size, sizeof(size));
	//Write file to stream
	cout << "Recuperando " << size << " bytes" << endl;
	deque<char>& outputVector = *(new deque<char>());
	for (int i = 0; i < size; i++) {
		outputVector.push_back(outputDeque.front());
		outputDeque.pop_front();
	}
	string ext;
	//Retrieve file extension
	char c;
	while ((c = outputDeque.front()) != '\0') {
		ext.push_back(c);
		outputDeque.pop_front();
	}
	ofstream& outputFile = *(new ofstream(output + ext, ios::binary));
	while (!outputVector.empty()) {
		outputFile << outputVector.front();
		outputVector.pop_front();
	}
	hostFile.close();
	outputFile.close();
}

template<class type>
void BMPStenographier::pushElement(vector<char>& vector, type num) {
	for (int i = sizeof(num) - 1; i >= 0; i--) {
		char value = (num >> (8 * i)) & 0x0FF;
		vector.push_back(value);
	}
}

void BMPStenographier::popElement(deque<char>& deque, int* num, size_t bytes) {
	*num = 0;
	for (size_t i = 0; i < bytes; i++) {
		char c = deque.front();
		*num <<= 8;
		*num |= (0x0FF & c);
		deque.pop_front();
	}
}

vector<char>& BMPStenographier::prepareVector(vector<char>& secretData,
		string secret) {
	int size = secretData.size();
	vector<char>& secretVector = *(new vector<char>());
	//Pusheo el tamano del archivo
	pushElement(secretVector, size);
	//Pusheo el archivo
	cout << "Leyendo " << secretData.size() << " bytes de archivo" << endl;
	for (size_t i = 0; i < secretData.size(); i++) {
		secretVector.push_back(secretData.at(i));
	}
	string ext = secret.substr(secret.find_last_of('.'));
	//Pusheo la extension
	for (size_t i = 0; i < ext.length(); i++) {
		secretVector.push_back(ext.at(i));
	}
	secretVector.push_back('\0');
	return secretVector;
}

ifstream* BMPStenographier::loadFile(string path) {
	ifstream* file = new ifstream(path, ios::in | ios::binary);
	if (!file) {
		cerr << "Fallo el leer " << path << endl;
		throw "Fallo el leer el archivo";
	}
	return file;
}

vector<char>& BMPStenographier::convertToArray(ifstream& file) {
	size_t start = file.tellg();
	file.seekg(0, file.end);
	size_t end = file.tellg();
	size_t size = end - start;
	file.seekg(start);
	char* buffer = new char[size];
	file.read(buffer, size);
	vector<char>* values = new vector<char>();
	for (size_t i = 0; i < size; i++) {
		values->push_back(buffer[i]);
	}
	return *values;
}

