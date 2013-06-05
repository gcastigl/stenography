#include <sg/encription/Encription.h>
#include <openssl/evp.h>
#include <cstring>
#include <stdio.h>

vector<char>& Aes128EncriptionStrategy::encript(EncriptionBlockType mode, vector<char>& input) {
	unsigned char key[TAM_CLAVE];
	unsigned char iv[TAM_CLAVE];
	const unsigned char * password = (const unsigned char *)getPassword();
	EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
	EVP_CIPHER_CTX ctx;
	int inl, outl, templ;
	unsigned char * out = (unsigned char *)malloc(1024);

	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);
	inl = input.size();
	EVP_EncryptUpdate(&ctx, out, &outl, (unsigned char *)input.data(), inl);
	EVP_EncryptFinal_ex(&ctx, out + outl, &templ);
	outl +=templ;

	EVP_CIPHER_CTX_cleanup(&ctx);

	vector<char>* outVector = new vector<char>();
	for(int i = 0; i < outl; i++){
		outVector->push_back((char)(out[i]));
	}
	return *outVector;
}

vector<char>& Aes128EncriptionStrategy::decript(EncriptionBlockType mode, vector<char>& input) {
	unsigned char key[TAM_CLAVE];
	unsigned char iv[TAM_CLAVE];
	const unsigned char * password = (const unsigned char *)getPassword();
	EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
	EVP_CIPHER_CTX ctx;
	int inl, outl, templ;
	unsigned char * out = (unsigned char *)malloc(1024);

	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx, EVP_aes_128_cbc(), NULL, key, iv);
	inl = input.size();
	EVP_DecryptUpdate(&ctx, out, &outl, (unsigned char *)input.data(), inl);
	EVP_DecryptFinal_ex(&ctx, out + outl, &templ);
	outl +=templ;

	EVP_CIPHER_CTX_cleanup(&ctx);

	vector<char>* outVector = new vector<char>();
	for(int i = 0; i < outl; i++){
		outVector->push_back((char)(out[i]));
	}
	return *outVector;
}
