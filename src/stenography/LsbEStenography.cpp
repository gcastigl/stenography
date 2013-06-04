#include <sg/stenography/Stenography.h>

#include <vector>
#include <deque>
#include <iostream>

using namespace std;

bool LsbEStenography::embedable(vector<char>& host, vector<char>& secret) {
	size_t embeddableBytes = 0;
	for (size_t i = 0; i < host.size(); i++) {
		char c = host.at(i);
		if (c == c1 || c == c2) {
			embeddableBytes++;
		}
	}
	return secret.size() * 8 <= embeddableBytes;
}

void LsbEStenography::embed(char hide, vector<char>& hostArray, size_t& index) {
	int bit;
	while (bit < 8) {
		char c = hostArray.at(index);
		if (c == c1 || c == c2) {
			hostArray.at(index) = embedByte(hide, hostArray.at(index), bit, 1);
			bit++;
		}
		index++;
	}
}

deque<char>& LsbEStenography::extract(vector<char>& host) {
	char lowerMask = 0x0FF << 1;
	char upperMask = ~lowerMask;
	deque<char>& output = *(new deque<char>());
	char c = 0;
	cout << "Parseando " << host.size() << " bytes" << endl;
	int offset = 0;
	for (size_t i = 0; i < host.size(); i++) {
		unsigned char current = host.at(i);
		if (current == 0x0FE || current == 0x0FF) {
 			c |= (current & upperMask);
			offset++;
			if (offset == 8) {
				output.push_back(c);
				c = 0;
				offset = 0;
			}
			c <<= 1;
		}
	}
	return output;
}

