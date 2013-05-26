#include "Stenography.h"
#include <iostream>
#include <deque>

using namespace std;

deque<char>& Lsb1Stenography::embed(deque<char>& host, deque<char>& secret) {
	deque<char> * vec = new deque<char>(host);
	return *vec;
}

deque<char>& Lsb1Stenography::extract(deque<char>& host) {
	return host;
}
