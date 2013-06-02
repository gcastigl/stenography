#pragma once

#include <string>
#include <vector>
#include <deque>

class Stenography;
class EncriptionStrategy;

using namespace std;

class BMPStenographier {
public:
	void embed(string hostFile, string secretFile, string outputFile, Stenography& stenographer, EncriptionStrategy* encriptionStrategy);
	void extract(string hostFile, string outputFile, Stenography& stenographer, EncriptionStrategy* encriptionStrategy);
private:
	static const int HEADER_SIZE = 54;
	ifstream* loadFile(string path);
	vector<char>& convertToArray(ifstream& file);
	vector<char>& prepareVector(vector<char>& secretData, string secret);
	template <class type>
	void pushElement(vector<char>& vector, type num);
	void popElement(deque<char>& vector, int* num, size_t bytes);
};


