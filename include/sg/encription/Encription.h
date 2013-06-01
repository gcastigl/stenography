#pragma once

class EncriptionStrategy {
	public:
		virtual ~EncriptionStrategy() {};
		virtual void encript() = 0;
		virtual void decript() = 0;
};

class Aes128EncriptionStrategy : public EncriptionStrategy {
	public:
		~Aes128EncriptionStrategy() {};
		void encript();
		void decript();
};

/*
class Aes193EncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};

class Aes1999EncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};

class PezEncriptionStrategy : public EncriptionStrategy {
	public:
		void encript();
		void decript();
};
*/
