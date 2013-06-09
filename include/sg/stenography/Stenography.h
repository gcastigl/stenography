#pragma once

#include <fstream>
#include <vector>
#include <deque>

using namespace std;

class Stenography {
	public:
		virtual ~Stenography() {};
		bool embed(vector<char>& host, vector<char>& secret, ofstream& outfile);
		virtual deque<char>& extract(vector<char>& host) = 0;
	protected:
		bool embedable(vector<char>& host, vector<char>& secret);
		virtual size_t hostCapacity(vector<char>& host) = 0;
		virtual size_t secretSize(vector<char>& secret) = 0;
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
		size_t hostCapacity(vector<char>& host);
		size_t secretSize(vector<char>& secret);
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
		size_t hostCapacity(vector<char>& host);
		size_t secretSize(vector<char>& secret);
		void embed(char hide, vector<char>& hostArray, size_t& index);
	private:
		static const char c1 = 0x0FE;
		static const char c2 = 0x0FF;
};

