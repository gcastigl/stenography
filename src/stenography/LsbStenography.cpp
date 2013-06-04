#include <iostream>
#include <deque>

#include <sg/stenography/Stenography.h>

using namespace std;

LsbStenography::LsbStenography(int bits) :
	bits(bits) {
}

bool LsbStenography::embedable(vector<char>& host, vector<char>& secret) {
	return secret.size() * 8 / bits <= host.size();
}

void LsbStenography::embed(char hide, vector<char>& hostArray, size_t& index) {
	for (unsigned int bit = 0; bit < 8; bit += bits) {
		hostArray.at(index) = embedByte(hide, hostArray.at(index), bit, bits);
		index++;
	}
}

deque<char>& LsbStenography::extract(vector<char>& host) {
	char lowerMask = 0xFF << bits;
	char upperMask = ~lowerMask;
	deque<char>& output = *(new deque<char>());
	char c = 0;
	int halfBits = (8 / bits);
	cout << "Parseando " << host.size() << " bytes" << endl;
	for (size_t i = 0 ; i < host.size() ; i++, c <<= bits) {
		int offset = i % halfBits;
		char current = host.at(i) & upperMask;
		c |= current;
		if (offset == halfBits - 1) {
			output.push_back(c);
			c = 0;
		}
	}
	return output;
}
