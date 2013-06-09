#include <sg/encription/EncriptionStrategy.h>
#include <openssl/evp.h>
#include <cstring>
#include <stdio.h>

const EVP_CIPHER * DesEncriptionStrategy::getType(EncriptionBlockType mode){
	const EVP_CIPHER * type;
	switch(mode){
		case CBC:
			type = EVP_des_cbc(); break;
		case OFB:
			type = EVP_des_ofb(); break;
		case CFB:
			type = EVP_des_cfb8(); break;
		case ECB:
			type = EVP_des_ecb(); break;
	}
	return type;
}

vector<char>& DesEncriptionStrategy::encript(vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_encrypt(type, input);
}

vector<char>& DesEncriptionStrategy::decript(vector<char>& input) {
	const EVP_CIPHER * type = getType(mode);
	return evp_decrypt(type, input);
}
