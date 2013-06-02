#include <sg/encription/EncryptionUtils.h>
#include <cstring>

#include <openssl/aes.h>

EncriptionUtils::EncriptionUtils() {

}

EncriptionUtils::~EncriptionUtils() {
	// TODO Auto-generated destructor stub
}

unsigned char * EncriptionUtils::padding(char *in, int *inl, size_t blocksize) {
	int pad;
	int i;
	unsigned char *inPad;
	pad = blocksize - (*inl) % blocksize;
	inPad = (unsigned char *) malloc(*inl + pad);
	memcpy(inPad, in, *inl);
	for (i = (*inl); i < (*inl + pad); i++)
		inPad[i] = pad;
	*inl += pad;
	return (inPad);
}

void printChars(unsigned char * vec, int size){
	printf("--..");
	for(int i= 0; i < size; i++){
		printf("%c", vec[i]);
	}
	printf("..--\n");
}

int EncriptionUtils::encrypt(unsigned char *in, int inl, unsigned char * out,
		AES_KEY *ks) {
	unsigned char inB[AES_BLOCK_SIZE];
	unsigned char outB[AES_BLOCK_SIZE];
	int numB;
	int i;
	numB = inl / AES_BLOCK_SIZE;
	for (i = 0; i < numB; i++) {
		memcpy(inB, in + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE);
		printChars(inB, AES_BLOCK_SIZE);
		AES_ecb_encrypt(inB, outB, ks, AES_ENCRYPT);
		//printf("-%d--<\n",i);
		memcpy(out + i * AES_BLOCK_SIZE, outB, AES_BLOCK_SIZE);
	}
	return 1;
}


