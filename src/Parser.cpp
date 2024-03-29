#include <sg/Parser.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <string>
#include <iostream>

template <typename T>
class EnumParser {
    map <string, T> enumMap;
public:
    EnumParser(){};
    T ParseEnum(const string &value) {
    	if (enumMap.find(value) != enumMap.end()) {
    		return enumMap.find(value)->second;
    	}
    	throw value;
    }
};


template <>
EnumParser<StenographyType>::EnumParser() {
    enumMap["LSB1"] = LSB1;
    enumMap["LSB4"] = LSB4;
    enumMap["LSBE"] = LSBE;
}

template <>
EnumParser<EncriptionType>::EnumParser() {
    enumMap["AES128"] = AES128;
    enumMap["AES192"] = AES192;
    enumMap["AES256"] = AES256;
    enumMap["DES"] = DES;
    enumMap["NONE"] = NONE;
}

template <>
EnumParser<EncriptionBlockType>::EnumParser() {
    enumMap["ECB"] = ECB;
    enumMap["CFB"] = CFB;
    enumMap["OFB"] = OFB;
    enumMap["CBC"] = CBC;
}

using namespace std;

string stringToUpper(string s) {
	std::string ret(s.size(), char());
	for(unsigned int i = 0; i < s.size(); ++i) {
		ret[i] = (s[i] <= 'z' && s[i] >= 'a') ? s[i]-('a'-'A') : s[i];
	}
	return ret;
}

Command* Parser::parseCommand(int argc, char *argv[]) {
	if (argc <= 1) {
		printUsage();
		return NULL;
	}
	Command* cmd = new Command;
	EnumParser<StenographyType> stenoraphyParser;
	EnumParser<EncriptionType> encriptionParser;
	EnumParser<EncriptionBlockType> encriptionBlockParser;
	for (int i = 1; i < argc; i++) {
		char* param = argv[i];
		if (strcmp("-help", param) == 0) {
			printUsage();
			return NULL;
		} else if (strcmp("-embed", param) == 0) {
			cmd->action = new ActionType(EMBED);
		} else if (strcmp("-extract", param) == 0) {
			cmd->action = new ActionType(EXTRACT);
		} else if (strcmp("-in", param) == 0) {
			i++;
			cmd->inputFile = string(argv[i]);
		} else if (strcmp("-p", param) == 0) {
			i++;
			cmd->hostFile = string(argv[i]);
		} else if (strcmp("-out", param) == 0) {
			i++;
			cmd->outputFile = string(argv[i]);
		} else if (strcmp("-steg", param) == 0) {
			i++;
			try {
				cmd->stenography = new StenographyType(stenoraphyParser.ParseEnum(stringToUpper(string(argv[i]))));
			} catch (string& err) {
				cout << "valor invalido " << param << " " << argv[i] << endl;
			}
		} else if (strcmp("-a", param) == 0) {
			i++;
			try {
				string toupper = string(argv[i]);
				cmd->encription = new EncriptionType(encriptionParser.ParseEnum(stringToUpper(string(argv[i]))));
			} catch (string& err) {
				cout << "valor invalido " << param << " " << argv[i] << endl;
			}
		} else if (strcmp("-m", param) == 0) {
			i++;
			try {
				cmd->encriptionBlock = new EncriptionBlockType(encriptionBlockParser.ParseEnum(stringToUpper(string(argv[i]))));
			} catch (string& err) {
				cout << "valor invalido " << param << " " << argv[i] << endl;
			}
		} else if (strcmp("-pass", param) == 0) {
			i++;
			cmd->password = string(argv[i]);
		} else {
			cout << "Parametro invalido: " << string(param) << endl;
		}
	}
	if (cmd->action == NULL) {
		printf("El parametro -embed o -extract es requerido\n");
		return NULL;
	} else if (*cmd->action == EMBED) {
		if (cmd->inputFile.empty() || cmd->hostFile.empty() || cmd->outputFile.empty() || cmd->stenography == NULL) {
			printf("Faltan parametros obligatorios. Invoque el programa con -help para ver parametros\n");
			return NULL;
		}
		if ((cmd->encription != NULL || cmd->encriptionBlock != NULL) && cmd->password.empty()) {
			printf("La contraseña es obligatoria si se desea encriptar\n");
			return NULL;
		}
	} else if (*cmd->action == EXTRACT) {
		if (cmd->hostFile.empty() || cmd->outputFile.empty() || !cmd->stenography) {
			printf("Faltan parametros obligatorios. Invoque el programa con -help para ver parametros\n");
			return NULL;
		}
		if ((cmd->encription != NULL || cmd->encriptionBlock != NULL) && cmd->password.empty()) {
			printf("La contraseña es obligatoria si se desea desencriptar\n");
			return NULL;
		}
	}
	return cmd;
}

void Parser::printUsage() {
	printf(
	"Uso del programa\n"
	"Para ocultar informacion:\n"
		"\t-embed\n\t\tIndica que se va a ocultar información.\n"
		"\t-in file\n\t\tArchivo que se va a ocultar.\n"
		"\t-p bitmapfile\n\t\tArchivo bmp que será el portador.\n"
		"\t-out bitmapfile\n\t\tArchivo bmp de salida, es decir, el archivo bitmapfile con la información de file incrustada.\n"
		"\t-steg <LSB1 | LSB4 | LSBE>\n\t\talgoritmo de esteganografiado: LSB de 1bit, LSB de 4 bits, LSB Enhanced\n"
		"\tParámetros opcionales:\n"
		"\t-a <aes128 | aes192 | aes256 | des>\n"
		"\t-m <ecb | cfb | ofb | cbc>\n"
		"\t-pass password (password de encripcion)\n"
		"\n\t=============================\n\n"
	"Para recuperar informacion:\n"
		"\t-extract\n\t\tIndica que se va a extraer información.\n"
		"\t-p bitmapfile\n\t\tArchivo bmp portador\n"
		"\t-out file\n\t\tArchivo de salida obtenido\n"
		"\t-steg <LSB1 | LSB4 | LSBE>\n\t\talgoritmo de esteganografiado: LSB de 1bit, LSB de 4 bits, LSB Enhanced\n"
		"\tParámetros opcionales:\n"
		"\t-a <aes128 | aes192 | aes256 | des>\n"
		"\t-m <ecb | cfb | ofb | cbc>\n"
		"\t-pass password (password de encripcion)\n"
	);
}
