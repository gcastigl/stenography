#pragma once

#include <fstream>
#include <deque>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		void embed(ifstream& host, ifstream& secret, ofstream& outfile);
		virtual deque<char>& extract(deque<char>& host) = 0;
	protected:
		virtual bool embedable(ifstream& host, ifstream& secret) = 0;
		virtual void embed(char hide, deque<char>* hostDeque, char* stenographied, u_int& index) = 0;
	private:
		deque<char>* convertoToDeque(ifstream& file);
};

class Lsb1Stenography : public Stenography {
	public:
		~Lsb1Stenography() {};
		deque<char>& extract(deque<char>& host);
	protected:
		bool embedable(ifstream& host, ifstream& secret);
		void embed(char hide, deque<char>* hostDeque, char* stenographied, u_int& index);
};