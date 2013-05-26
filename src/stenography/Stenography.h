#ifndef STENOGRAPHY_H_
#define STENOGRAPHY_H_

#include <deque>

using namespace std;

class Stenography {
	public:
		virtual deque<char>& embed(deque<char>& host, deque<char>& secret) = 0;
		virtual deque<char>& extract(deque<char>& host) = 0;
};

class Lsb1Stenography : public Stenography {
	public:
		deque<char>& embed(deque<char>& host, deque<char>& secret);
		deque<char>& extract(deque<char>& host);
};

#endif
