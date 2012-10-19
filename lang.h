#include <vector>

#ifndef LANG_H
#define LANG_H

class Type {
	public:
		Type();
		unsigned char getSize();
		bool getSigned();
		
	protected:
		unsigned char size;
		bool sign;
		std::vector<unsigned char> *val;
};

class Byte : public Type {
	public:
		Byte();
};

class Word : public Type {
	public:
		Word();
};

class Doub : public Type {
	public:
		Doub();
};

class Quad : public Type {
	public:
		Quad();
};

class VLen {
	public:
		VLen(bool hasTerm, std::vector<unsigned char> *tid, int length);
		int getLen();
		std::vector<unsigned char> *getTerm();
		std::vector<unsigned char> *getLenID();
		bool hasTerm();
		
	private:
		bool hasTerminator;
		std::vector<unsigned char> *terminator;
		std::vector<unsigned char> *lengthIdentifier;
		int length;
};


#endif
