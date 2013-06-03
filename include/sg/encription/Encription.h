#pragma once
#include <vector>

using namespace std;

enum EncryptionMode {CBC, OFB, CFB, ECB};

class EncryptionStrategy {
	public:
		virtual ~EncryptionStrategy() {};
		virtual vector<char>& encript(EncryptionMode mode, const unsigned char * password, vector<char>& input) = 0;
		virtual vector<char>& decript(EncryptionMode mode, unsigned char * password, vector<char>& input) = 0;
};

class Aes128EncriptionStrategy : public EncryptionStrategy {
	public:
		~Aes128EncriptionStrategy() {};
		vector<char>& encript(EncryptionMode mode, const unsigned char * password, vector<char>& input);
		vector<char>& decript(EncryptionMode mode, unsigned char * password, vector<char>& input);
};

/*
class Aes193EncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};

class Aes1999EncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};

class PezEncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};
*/
