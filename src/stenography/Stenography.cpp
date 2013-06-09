#include <sg/stenography/Stenography.h>
#include <sg/exception.h>
#include <fstream>
#include <iostream>
#include <array>

using namespace std;

bool Stenography::embed(vector<char>& host, vector<char>& secret, ofstream& outfile) {
	if (!embedable(host, secret)) {
		return false;
	}
	size_t index = 0;
	cout << "Estenografiando bytes a host..." << endl;
	for (size_t i = 0; i < secret.size(); i++) {
		char hide = secret.at(i);
		embed(hide, host, index);
	}
	// Fill buffer with remaining vales from host bytes
	outfile.write(host.data(), host.size());
	cout << "Estenografiado finalizado correctamente" << endl;
	return true;
}

bool Stenography::embedable(vector<char>& host, vector<char>& secret) {
	size_t hostCapacity = this->hostCapacity(host);
	size_t secretSize = this->secretSize(secret);
	bool embeddable = secretSize <= hostCapacity;
	if (!embeddable) {
		cout << "Tamaño de archivo insuficiente" <<  endl;
		cout << "Capacidad de host: " << hostCapacity << endl;
		cout << "Tamaño requerido: " << secretSize << endl;
	}
	return embeddable;
}

char Stenography::embedByte(char hide, char embedTo, int bit, int bitsToEmbed) {
	char lowerMask = 0x0FF << bitsToEmbed;
	char upperMask = ~lowerMask;
	char value = (hide >> (8 - bit - bitsToEmbed)) & upperMask;
	return (embedTo & lowerMask) + value;
}
