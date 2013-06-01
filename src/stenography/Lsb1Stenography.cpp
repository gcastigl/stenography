#include <sg/stenography/Stenography.h>
#include <sg/exception.h>
#include <iostream>
#include <deque>

using namespace std;

deque<char>* Lsb1Stenography::embed(ifstream& host, ifstream& secret) {
	if (!embedable(host, secret)) {
		throw new IllegalArgumentException("secret does not fit into host!!");
	}
	deque<char>* secretDeque = convertoToDeque(secret);
	deque<char>* hostDeque = convertoToDeque(host);
	unsigned int j = 0;
	for (unsigned int i = 0 ; i < secretDeque->size() ; i++) {
		char c = secretDeque->at(i);
		for (unsigned int bit = 0; bit < 8 ; bit++) {
			char value = (c >> bit) & 1;
			char originalValue = hostDeque->at(j);
			hostDeque->at(j) = (originalValue & 0xFE) + value;
			j++;
		}
	}
	return hostDeque;
}

bool Lsb1Stenography::embedable(ifstream& host, ifstream& secret) {
	// Check that secret can be embeddable inside host
	return true;
}

deque<char>& Lsb1Stenography::extract(deque<char>& host) {
	return host;
}
