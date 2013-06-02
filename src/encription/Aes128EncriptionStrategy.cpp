#include <sg/encription/Encription.h>
#include <sg/encription/EncryptionUtils.h>
#include <openssl/aes.h>

vector<char>& Aes128EncriptionStrategy::encript(EncryptionMode mode, unsigned char * password, vector<char>& input) {
	unsigned char *inPad;
	AES_KEY ks;
	AES_set_encrypt_key((unsigned char *)"0123456789012345", 128, &ks);
	unsigned char iv[] = "5432109876543210";
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

vector<char>& Aes128EncriptionStrategy::decript(EncryptionMode mode, unsigned char * password, vector<char>& input) {
		AES_KEY ks;
		AES_set_encrypt_key((unsigned char *)"0123456789012345", 128, &ks);
		unsigned char iv[] = "5432109876543210";
		int inl = input.size();

		unsigned char * out = (unsigned char *)malloc (inl);

		AES_cbc_encrypt((unsigned char *)input.data(), out, inl, &ks, iv, AES_DECRYPT);

		vector<char>* outVector = new vector<char>();
		for(int i = 0; i < inl; i++){
			outVector->push_back((char)(out[i]));
		}
		return *outVector;
}
