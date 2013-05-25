#include "BMPImage.h"

int main() {
	BMPImage img("test.bmp");
	img.embedFile("test.txt", "output", 4);
}
