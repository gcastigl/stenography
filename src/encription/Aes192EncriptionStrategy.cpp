#include <sg/encription/EncriptionStrategy.h>
#include <openssl/evp.h>
#include <cstring>
#include <stdio.h>

const EVP_CIPHER * Aes192EncriptionStrategy::getType(EncriptionBlockType mode){
	const EVP_CIPHER * type;
	switch(mode){
		case CBC:
			type = EVP_aes_192_cbc(); break;
		case OFB:
			type = EVP_aes_192_ofb(); break;
		case CFB:
			type = EVP_aes_192_cfb8(); break;
		case ECB:
			type = EVP_aes_192_ecb(); break;
	}
	return type;
}

vector<char>& Aes192EncriptionStrategy::encript(EncriptionBlockType mode, vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_encrypt(type, input);
}

vector<char>& Aes192EncriptionStrategy::decript(EncriptionBlockType mode, vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_decrypt(type, input);
}
