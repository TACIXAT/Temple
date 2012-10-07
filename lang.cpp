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
