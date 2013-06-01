#pragma once

#include <fstream>
#include <deque>
#include <vector>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		void embed(ifstream& host, ifstream& secret, ofstream& outfile);
		void extract(ifstream& host, ofstream& outfile);
	protected:
		virtual bool embedable(ifstream& host, ifstream& secret) = 0;
		virtual void embed(char hide, vector<char>& hostArray, u_int& index) = 0;
	private:
		vector<char>& convertToArray(ifstream& file);
};

class LsbStenography : public Stenography {
	public:
		LsbStenography(int bits);
		~LsbStenography() {};
	protected:
		bool embedable(ifstream& host, ifstream& secret);
		void embed(char hide, vector<char>& hostArray, u_int& index);
	private:
		int bits;
};
