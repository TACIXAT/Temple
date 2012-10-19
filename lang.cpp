#include "lang.h"

Type::Type() {
	size = 0x1;
	sign = false;
} 

unsigned char Type::getSize(){
	return size;
}

bool Type::getSigned(){
	return sign;
}

Byte::Byte() {
	size = 0x1;
	sign = false;
} 

Word::Word() {
	size = 0x2;
	sign = false;
} 

Doub::Doub() {
	size = 0x4;
	sign = false;
} 

Quad::Quad() {
	size = 0x8;
	sign = false;
} 

VLen::VLen(bool hasTerm, std::vector<unsigned char> *tid, int len) {
	hasTerminator = hasTerm;
	length = len;
	
	if(hasTerminator){
		terminator = tid;
	} else {
		lengthIdentifier = tid;
	}
} 

int VLen::getLen() {
	return length;
}

std::vector<unsigned char> *VLen::getTerm() {
	return terminator;
}

std::vector<unsigned char> *VLen::getLenID() {
	return lengthIdentifier;
}

bool VLen::hasTerm() {
	return hasTerminator;
}


