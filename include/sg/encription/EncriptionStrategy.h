#pragma once
#include <vector>
#include <sg/Parser.h>
#include <openssl/evp.h>
#include <cstring>

using namespace std;

#define TAM_CLAVE 16

class ICrypto
{
    public:
        virtual ~ICrypto() {}
        virtual vector<char>& encript(EncriptionBlockType mode, vector<char>& input) = 0;
        virtual vector<char>& decript(EncriptionBlockType mode, vector<char>& input) = 0;
};

class EncriptionStrategy  {
	public:
		EncriptionStrategy(const char * password) :
			password(password) {
		};
		virtual ~EncriptionStrategy() {};
		vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
		vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
	protected :
		virtual const EVP_CIPHER * getType(EncriptionBlockType mode) = 0;
		vector<char>& evp_encrypt(const EVP_CIPHER * type, vector<char>& input) {
			unsigned char key[TAM_CLAVE];
			unsigned char iv[TAM_CLAVE];
			const unsigned char * password = (const unsigned char *)getPassword();
			EVP_BytesToKey(type, EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
			EVP_CIPHER_CTX ctx;
			int inl, outl, templ;
			unsigned char * out = (unsigned char *)malloc((input.size() + 16 ) * sizeof(char));

			EVP_CIPHER_CTX_init(&ctx);
			EVP_EncryptInit_ex(&ctx, type, NULL, key, iv);
			inl = input.size();
			EVP_EncryptUpdate(&ctx, out, &outl, (unsigned char *)input.data(), inl);
			EVP_EncryptFinal_ex(&ctx, out + outl, &templ);
			outl +=templ;

			EVP_CIPHER_CTX_cleanup(&ctx);

			vector<char>* outVector = new vector<char>();
			for(int i = 0; i < outl; i++){
				outVector->push_back((char)(out[i]));
			}
			free(out);
			return *outVector;
		};
		vector<char>& evp_decrypt(const EVP_CIPHER * type, vector<char>& input) {
			unsigned char key[TAM_CLAVE];
			unsigned char iv[TAM_CLAVE];
			const unsigned char * password = (const unsigned char *)getPassword();
			EVP_BytesToKey(type, EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
			EVP_CIPHER_CTX ctx;
			int inl, outl, templ;
			unsigned char * out = (unsigned char *)malloc((input.size() + 16 ) * sizeof(char));

			EVP_CIPHER_CTX_init(&ctx);
			EVP_DecryptInit_ex(&ctx, type, NULL, key, iv);
			inl = input.size();
			EVP_DecryptUpdate(&ctx, out, &outl, (unsigned char *)input.data(), inl);
			EVP_DecryptFinal_ex(&ctx, out + outl, &templ);
			outl +=templ;

			EVP_CIPHER_CTX_cleanup(&ctx);

			vector<char>* outVector = new vector<char>();
			for(int i = 0; i < outl; i++){
				outVector->push_back((char)(out[i]));
			}
			free(out);
			return *outVector;
		};
		const char * getPassword() const {
			return password;
		}
	private:
		const char * password;
};

class Aes128EncriptionStrategy : public EncriptionStrategy, public ICrypto {
	public:
		Aes128EncriptionStrategy(const char * password) : EncriptionStrategy(password){}
		~Aes128EncriptionStrategy() {};
		const EVP_CIPHER * getType(EncriptionBlockType mode);
		vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
		vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
};


class Aes192EncriptionStrategy : public EncriptionStrategy, public ICrypto {
public:
	Aes192EncriptionStrategy(const char * password) : EncriptionStrategy(password){}
	~Aes192EncriptionStrategy() {};
	const EVP_CIPHER * getType(EncriptionBlockType mode);
	vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
	vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
};

class Aes256EncriptionStrategy : public EncriptionStrategy, public ICrypto {
public:
	Aes256EncriptionStrategy(const char * password) : EncriptionStrategy(password){}
	~Aes256EncriptionStrategy() {};
	const EVP_CIPHER * getType(EncriptionBlockType mode);
	vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
	vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
};

class DesEncriptionStrategy : public EncriptionStrategy, public ICrypto {
public:
	DesEncriptionStrategy(const char * password) : EncriptionStrategy(password){}
	~DesEncriptionStrategy() {};
	const EVP_CIPHER * getType(EncriptionBlockType mode);
	vector<char>& encript(EncriptionBlockType mode, vector<char>& input);
	vector<char>& decript(EncriptionBlockType mode, vector<char>& input);
};
