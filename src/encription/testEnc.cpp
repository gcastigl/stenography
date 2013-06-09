#include <stdio.h>
#include <iostream>
#include <deque>
#include <sg/Parser.h>
#include <sg/stenography/Stenography.h>
#include <sg/encription/EncriptionStrategy.h>
#include <sg/stenography/BMPStenographier.h>

using namespace std;

const char * evaluate(vector<char>& in, vector<char>& decripted);

ifstream* loadFile(string path) {
	ifstream* file = new ifstream(path, ios::in | ios::binary);
	if (!file) {
		cerr << "Fallo el leer " << path << endl;
		throw "Fallo el leer el archivo";
	}
	return file;
}

vector<char>& convertToArray(ifstream& file) {
	size_t start = file.tellg();
	file.seekg(0, file.end);
	size_t end = file.tellg();
	size_t size = end - start;
	file.seekg(start);
	char* buffer = new char[size];
	file.read(buffer, size);
	vector<char>* values = new vector<char>();
	for (size_t i = 0; i < size; i++) {
		values->push_back(buffer[i]);
	}
	return *values;
}
/*
int main(){
	ifstream& secretFile = *loadFile("./res/testPampero/secret.txt");
	vector<char> input = convertToArray(secretFile);

	EVP_CIPHER_CTX_key_length(&ctx);
	  cipherIvLength  = EVP_CIPHER_CTX_iv_length(&ctx);
	unsigned char key[TAM_CLAVE];
	unsigned char iv[TAM_CLAVE];
	const unsigned char * password = (const unsigned char *)"secreto";
	EVP_BytesToKey(EVP_aes_256_cbc(), EVP_md5(), NULL, password, strlen((const char *)password),1, key, iv);
	for(int i = 0; i < TAM_CLAVE; i++){
		printf("%2x", key[i]);
	}
	printf("\n--");
	for(int i = 0; i < TAM_CLAVE; i++){
			printf("%2x", iv[i]);
		}
	fflush(stdout);
	EVP_CIPHER_CTX ctx;
	int inl, outl, templ;
	unsigned char * out = (unsigned char *)malloc((input.size() + 16 ) * sizeof(char));

	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv);
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

	ofstream& auxFile = *(new ofstream("./res/testPampero/encrypted", ios::binary));
	for(int i = 0; i < outVector->size(); i++){
		auxFile << outVector->at(i);
	}
	auxFile.close();

}
*/

int main_() {
	ICrypto* e = new Aes256EncriptionStrategy((const char *)"secreto");
	ifstream& secretFile = *loadFile("./res/testPampero/secret.txt");
	vector<char> secretData = convertToArray(secretFile);
	 vector<char> out, decripted;
	out = e->encript(CBC, secretData);

	ofstream& auxFile = *(new ofstream("./res/testPampero/encrypted", ios::binary));
	for(size_t i = 0; i < out.size(); i++){
	    			auxFile << out.at(i);
	    		}
	    		auxFile.close();

	decripted = e->decript(CBC, out);
	printf("%s\n",evaluate(secretData, decripted));
	secretFile.close();
	return 0;
}
/*
int main() {
  ICrypto* e = new Aes128EncriptionStrategy((const char *)"secreto");
  char * data = "0123456789345645464654646465";
  vector<char>* in = new vector<char>();
  vector<char> decripted;

  for(int i = 0; i < strlen(data); i++){
    in->push_back((char)(data[i]));
  }

  vector<char> out;

  out = e->encript(ECB, *in);
  decripted = e->decript(ECB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CFB, *in);
  decripted = e->decript(CFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(OFB, *in);
  decripted = e->decript(OFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CBC, *in);
  decripted = e->decript(CBC, out);
  printf("%s\n",evaluate(*in, decripted));

  e = new Aes192EncriptionStrategy((const char *)"MYPASS");

  out = e->encript(ECB, *in);
  decripted = e->decript(ECB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CFB, *in);
  decripted = e->decript(CFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(OFB, *in);
  ofstream& auxFile = *(new ofstream("./res/testPampero/resultApp", ios::binary));
    for(int i = 0; i < out.size(); i++){
    			auxFile << out.at(i);
    		}
    		auxFile.close();
  decripted = e->decript(OFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CBC, *in);
  decripted = e->decript(CBC, out);
  printf("%s\n",evaluate(*in, decripted));

  e = new Aes256EncriptionStrategy((const char *)"MYPASS");

  out = e->encript(ECB, *in);
  decripted = e->decript(ECB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CFB, *in);
  decripted = e->decript(CFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(OFB, *in);

  decripted = e->decript(OFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CBC, *in);
  decripted = e->decript(CBC, out);
  printf("%s\n",evaluate(*in, decripted));

  e = new DesEncriptionStrategy((const char *)"MYPASS");

  out = e->encript(ECB, *in);
  decripted = e->decript(ECB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CFB, *in);
  decripted = e->decript(CFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(OFB, *in);
  decripted = e->decript(OFB, out);
  printf("%s\n",evaluate(*in, decripted));

  out = e->encript(CBC, *in);
  decripted = e->decript(CBC, out);
  printf("%s\n",evaluate(*in, decripted));
}*/

const char * evaluate(vector<char>& in, vector<char>& decripted){
	if(in.size() != decripted.size()){
		return "ERROR";
	}
	for(size_t i= 0; i < in.size(); i++){
		if( in.at(i) != decripted.at(i) ){
			return "ERROR";
		}
	}
	return "OK";
}


