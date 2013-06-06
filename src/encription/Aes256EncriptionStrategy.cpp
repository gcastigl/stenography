#include <sg/encription/Encription.h>
#include <openssl/evp.h>
#include <cstring>
#include <stdio.h>

const EVP_CIPHER * Aes256EncriptionStrategy::getType(EncriptionBlockType mode){
	const EVP_CIPHER * type;
	switch(mode){
		case CBC:
			type = EVP_aes_256_cbc(); break;
		case OFB:
			type = EVP_aes_256_ofb(); break;
		case CFB:
			type = EVP_aes_256_cfb8(); break;
		case ECB:
			type = EVP_aes_256_ecb(); break;
	}
	return type;
}

vector<char>& Aes256EncriptionStrategy::encript(EncriptionBlockType mode, vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_encrypt(type, input);
}

vector<char>& Aes256EncriptionStrategy::decript(EncriptionBlockType mode, vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_decrypt(type, input);
}
