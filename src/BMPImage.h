#ifndef __BMPIMAGE__
#define __BMPIMAGE__

#include <string>
#include <fstream>

using namespace std;

class BMPImage {
        public:
                explicit BMPImage(string);
                void embedFile(string, string, int);
//              embedCipheredText(string, 
                static const int BUFFER_SIZE = 512;
		static const int HEADER_SIZE = 54;
        private:
		void maskBytes(const char *, const char *, int, int, char *);
                string filePath;
                int size;
		
};


#endif
