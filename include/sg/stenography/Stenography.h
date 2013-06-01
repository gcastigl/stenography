#pragma once

#include <fstream>
#include <vector>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		void embed(vector<char>& host, vector<char>& secret, ofstream& outfile);
		void extract(ifstream& host, ofstream& outfile);
	protected:
		virtual bool embedable(vector<char>& host, vector<char>& secret) = 0;
		virtual void embed(char hide, vector<char>& hostArray, u_int& index) = 0;
	private:
		vector<char>& convertToArray(ifstream& file);
};

class LsbStenography : public Stenography {
	public:
		LsbStenography(int bits);
		~LsbStenography() {};
	protected:
		bool embedable(vector<char>& host, vector<char>& secret);
		void embed(char hide, vector<char>& hostArray, u_int& index);
	private:
		int bits;
};
