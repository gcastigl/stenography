#pragma once

#include <sg/encription/EncriptionStrategy.h>
#include <string>
#include <vector>
#include <deque>

class Stenography;
class EncriptionStrategy;

using namespace std;

class BMPStenographier {
public:
	void embed(string hostFile, string secretFile, string outputFile, Stenography& stenographer, ICrypto* encriptionStrategy, EncriptionBlockType mode);
	void extract(string hostFile, string outputFile, Stenography& stenographer, ICrypto* encriptionStrategy, EncriptionBlockType mode);
private:
	static const int HEADER_SIZE = 54;
	ifstream* loadFile(string path);
	vector<char>& convertToArray(ifstream& file);
	vector<char>& prepareVector(vector<char>& secretData, string secret);
	template <class type>
	void pushElement(vector<char>& vector, type num);
	void popElement(deque<char>& vector, uint* num, size_t bytes);
};


