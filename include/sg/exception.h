#pragma once

#include <exception>

class StegnographySizeException: public std::exception {
private:
	long maxSize;
public:
	StegnographySizeException(long maxSize) :
			maxSize(maxSize) {
	}
};
