#include <iostream>
#include <deque>

#include <sg/stenography/Stenography.h>

using namespace std;

LsbStenography::LsbStenography(int bits) :
		bits(bits) {
}

bool LsbStenography::embedable(vector<char>& host, vector<char>& secret) {
	// Check that secret can be embeddable inside host
	return true;
}

void LsbStenography::embed(char hide, vector<char>& hostArray, size_t& index) {
	char lowerMask = 0xFF << bits;
	char upperMask = ~lowerMask;
	for (unsigned int bit = 0; bit < 8; bit += bits) {
		char value = (hide >> (8 - bit - 1)) & upperMask;
		char originalValue = hostArray.at(index);
		hostArray.at(index) = (originalValue & lowerMask) + value;
		index++;
	}
}

deque<char>& LsbStenography::extract(vector<char>& host) {
	char lowerMask = 0xFF << bits;
	char upperMask = ~lowerMask;
	deque<char>& output = *(new deque<char>());
	char c = 0;
	cout << "Parseando " << host.size() << " bytes" << endl;
	for (size_t i = 0 ; i < host.size() ; i++, c <<= bits) {
		int offset = i % (8 / bits);
		char current = host.at(i) & upperMask;
		c |= current;
		if (offset == 7) {
			output.push_back(c);
			c = 0;
		}
	}
	return output;
}
