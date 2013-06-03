#include <sg/stenography/Stenography.h>
#include <sg/exception.h>
#include <fstream>
#include <iostream>
#include <array>

using namespace std;

void Stenography::embed(vector<char>& host, vector<char>& secret, ofstream& outfile) {
	if (!embedable(host, secret)) {
		throw new IllegalArgumentException("secret does not fit into host!!");
	}
	size_t index = 0;
	cout << "Embedding bytes from secret to host" << endl;
	for (size_t i = 0; i < secret.size(); i++) {
		char hide = secret.at(i);
		embed(hide, host, index);
	}
	// Fill buffer with remaining vales from host bytes
	outfile.write(host.data(), host.size());
	cout << "stenography saved written successfully" << endl;
}
