#include <sg/stenography/BMPStenographier.h>
#include <sg/stenography/Stenography.h>
#include <sg/encription/Encription.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void BMPStenographier::embed(string host, string secret, string output,
		Stenography& stenographier, EncriptionStrategy* encriptionStrategy) {
	ifstream& hostFile = *loadFile(host);
	ifstream& secretFile = *loadFile(secret);
	char* headerBuffer = new char[HEADER_SIZE];
	hostFile.read(headerBuffer, HEADER_SIZE);
	ofstream& outputFile = *(new ofstream(output, ios::binary));
	outputFile.write(headerBuffer, HEADER_SIZE);
	vector<char> secretData = convertToArray(secretFile);
	vector<char>& secretVector = prepareVector(secretData, secret);
	stenographier.embed(convertToArray(hostFile), secretVector, outputFile);
	hostFile.close();
	secretFile.close();
	outputFile.close();
}

vector<char>& BMPStenographier::prepareVector(vector<char>& secretData,
		string secret) {
	int size = secretData.size();
	vector<char>& secretVector = *(new vector<char>());
	//Pusheo el tamano del archivo
	for (int i = sizeof(size) - 1; i >= 0; i--) {
		secretVector.push_back((size >> (8 * i)) & 0x0FF);
		cout << ((size >> (8 * i)) & 0x0FF) << endl;
	}
	//Pusheo el archivo
	cout << "Leyendo " << secretData.size() << " bytes de archivo" << endl;
	for (size_t i = 0; i < secretData.size(); i++) {
		cout << "Pusheo " << secretData.at(i) << endl;
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

void BMPStenographier::extract(string hostFile, string outputFile,
		Stenography& stenographier, EncriptionStrategy* encriptionStrategy) {

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

