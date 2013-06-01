#include <iostream>
#include <deque>

#include <sg/stenography/Stenography.h>

using namespace std;

LsbStenography::LsbStenography(int bits) :
		bits(bits) {
}

bool LsbStenography::embedable(ifstream& host, ifstream& secret) {
	// Check that secret can be embeddable inside host
	return true;
}

void LsbStenography::embed(char hide, vector<char>& hostArray, u_int& index) {
	char lowerMask = 0xFF << bits;
	char upperMask = !lowerMask;
	for (unsigned int bit = 0; bit < 8; bit += bits) {
		char value = (hide >> bit) & upperMask;
		char originalValue = hostArray.at(index);
		hostArray.at(index) = (originalValue & lowerMask) + value;
		index++;
	}
}
