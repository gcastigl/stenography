#pragma once;

#include <fstream>
#include <deque>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		virtual deque<char>* embed(ifstream& host, ifstream& secret) = 0;
		virtual deque<char>& extract(deque<char>& host) = 0;
	protected:
		deque<char>* convertoToDeque(ifstream& file);
};

class Lsb1Stenography : public Stenography {
	public:
		~Lsb1Stenography() {};
		deque<char>* embed(ifstream& host, ifstream& secret);
		deque<char>& extract(deque<char>& host);
	private:
		bool embedable(ifstream& host, ifstream& secret);
};
