#include <sg/encription/Encription.h>
#include <sg/encription/EncryptionUtils.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <cstring>
#include <stdio.h>

vector<char>& Aes128EncriptionStrategy::encript(EncriptionBlockType mode, vector<char>& input) {
	/* gets the key and iv from the password */
	unsigned char key[TAM_CLAVE];
	unsigned char iv[TAM_CLAVE];
	const unsigned char * password = (const unsigned char *)getPassword();
	switch(mode){
		case CBC:
			EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
			break;
		case OFB: EVP_BytesToKey(EVP_aes_128_ofb(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		case CFB: EVP_BytesToKey(EVP_aes_128_cfb1(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		case ECB: EVP_BytesToKey(EVP_aes_128_ecb(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		default:
			printf("ERROR: Invalid mode in decryption function.");
			exit(0);
	}
	unsigned char *inPad;
	AES_KEY ks;
	AES_set_encrypt_key(key, 128, &ks);
	int inl = input.size();
	EncriptionUtils * encryptionUtils = new EncriptionUtils();
	inPad = encryptionUtils->padding(input.data(), &inl, AES_BLOCK_SIZE);
	unsigned char * out = (unsigned char *)malloc (inl);
	AES_cbc_encrypt(inPad, out, inl, &ks, iv, AES_ENCRYPT);
	vector<char>* outVector = new vector<char>();
	for(int i = 0; i < inl; i++){
		outVector->push_back((char)(out[i]));
	}
	return *outVector;
}

vector<char>& Aes128EncriptionStrategy::decript(EncriptionBlockType mode, vector<char>& input) {
	/* gets the key and iv from the password */
	unsigned char key[TAM_CLAVE];
	unsigned char iv[TAM_CLAVE];
	const unsigned char * password = (const unsigned char *)getPassword();
	switch(mode){
		case CBC: EVP_BytesToKey(EVP_aes_128_cbc(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		case OFB: EVP_BytesToKey(EVP_aes_128_ofb(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		case CFB: EVP_BytesToKey(EVP_aes_128_cfb1(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		case ECB: EVP_BytesToKey(EVP_aes_128_ecb(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv); break;
		otherwise:
			printf("ERROR: Invalid mode in decryption function.");
			exit(0);
	}
	unsigned char *inPad;
	AES_KEY ks;
	AES_set_decrypt_key(key, 128, &ks);
	int inl = input.size();
	EncriptionUtils * encryptionUtils = new EncriptionUtils();
	unsigned char * out = (unsigned char *)malloc (inl);
	AES_cbc_encrypt((unsigned char *)input.data(), out, inl, &ks, iv, AES_DECRYPT);
	out = encryptionUtils->unpadding((char *)out, &inl);
	vector<char>* outVector = new vector<char>();
	for(int i = 0; i < inl; i++){
		outVector->push_back((char)(out[i]));
	}
	return *outVector;
}
