#include <sg/stenography/Stenography.h>
#include <iostream>
#include <deque>

using namespace std;

bool Lsb1Stenography::embedable(ifstream& host, ifstream& secret) {
	// Check that secret can be embeddable inside host
	return true;
}

void Lsb1Stenography::embed(char hide, deque<char>* hostDeque, char* stenographied, u_int& index) {
	for (unsigned int bit = 0; bit < 8 ; bit++) {
		char value = (hide >> bit) & 1;
		char originalValue = hostDeque->at(index);
		stenographied[index] = (originalValue & 0xFE) + value;
		index--;
	}
}

deque<char>& Lsb1Stenography::extract(deque<char>& host) {
	return host;
}
