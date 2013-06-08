#include <sg/encription/EncriptionStrategy.h>
#include <string.h>
#include <stdio.h>

char * evaluate(vector<char>& in, vector<char>& decripted);

int main_() {
  ICrypto* e = new Aes128EncriptionStrategy((const char *)"MYPASS");
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
}

char * evaluate(vector<char>& in, vector<char>& decripted){
	if(in.size() != decripted.size()){
		return "ERROR";
	}
	for(int i= 0; i < in.size(); i++){
		if( in.at(i) != decripted.at(i) ){
			return "ERROR";
		}
	}
	return "OK";
}
