#pragma once

#include <fstream>
#include <vector>
#include <deque>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		void embed(vector<char>& host, vector<char>& secret, ofstream& outfile);
		virtual deque<char>& extract(vector<char>& host) =0;
	protected:
		virtual bool embedable(vector<char>& host, vector<char>& secret) = 0;
		virtual void embed(char hide, vector<char>& hostArray, size_t& index) = 0;
		char embedByte(char hide, char embedTo, int bit, int bitsToEmbed);
	private:
		vector<char>& convertToArray(ifstream& file);
};

class LsbStenography : public Stenography {
	public:
		LsbStenography(int bits);
		~LsbStenography() {};
		deque<char>& extract(vector<char>& host);
	protected:
		bool embedable(vector<char>& host, vector<char>& secret);
		void embed(char hide, vector<char>& hostArray, size_t& index);
	private:
		int bits;
};

class LsbEStenography : public Stenography {
	public:
		LsbEStenography() {};
		~LsbEStenography() {};
		deque<char>& extract(vector<char>& host);
	protected:
		bool embedable(vector<char>& host, vector<char>& secret);
		void embed(char hide, vector<char>& hostArray, size_t& index);
	private:
		static const char c1 = 0x0FE;
		static const char c2 = 0x0FF;
};

