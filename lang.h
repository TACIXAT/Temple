#ifndef LANG_H
#define LANG_H

#include <vector>

class Type {
	public:
		Type();
		unsigned char getSize();
		bool getSigned();
		
	protected:
		unsigned char size;
		bool sign;
		std::vector<unsigned char> val;
};

class Byte : public Type {
	public:
		Byte();
};

class Word {
	public:
		Word();
};

class Doub {
	public:
		Doub();
};

class Quad {
	public:
		Quad();
};

#endif
