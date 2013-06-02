#pragma once

#include <string>
#include <openssl/aes.h>

class EncriptionUtils {
public:
	EncriptionUtils();
	virtual ~EncriptionUtils();
	unsigned char * padding(char *in, int *inl, size_t blocksize);
	int encrypt(unsigned char *in, int inl, unsigned char * out, AES_KEY *ks);
};
