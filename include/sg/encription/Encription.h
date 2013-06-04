#pragma once
#include <vector>
#include <sg/Parser.h>

using namespace std;

#define TAM_CLAVE 16

class EncryptionStrategy {
	public:
		EncryptionStrategy(const char * password) :
			password(password) {
		};
		virtual ~EncryptionStrategy() {};
		virtual vector<char>& encript(EncriptionBlockType mode, vector<char>& input) = 0;
		virtual vector<char>& decript(EncriptionBlockType mode, vector<char>& input) = 0;
	protected :
		const char * getPassword() const {
			return password;
		}
	private:
		const char * password;
};

class Aes128EncriptionStrategy : public EncryptionStrategy {
	public:
		Aes128EncriptionStrategy(const char * password) : EncryptionStrategy(password){}
		~Aes128EncriptionStrategy() {};
		vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
		vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
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
