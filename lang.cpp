#include "lang.h"

/*
	0x1 : BYTE
	0x2 : WORD 
	0x3 : DOUB
	0x4 : QUAD
	0x5 : NIBBLE
	0x6 : STRING
	0x7 : VLEN
	0x8 : MAGIC
	0x9 : BLOB
	0xA : ...
*/

TempleLang::TempleLang(){
	ll = new std::list<Container*>;
}

/* ==== CONTAINER ==== */
int TempleLang::Container::setName(std::string cname){
	name = cname;
	return 0;
}

std::string TempleLang::Container::getName(){
	return name;
}

int TempleLang::Container::setType(int ctype){
	type = ctype;
	return 0;
}

int TempleLang::Container::getType(){
	return type;
}

int TempleLang::Container::setSign(bool sign){
	hasSign = sign;
	return 0;
}

bool TempleLang::Container::getSign(){
	return hasSign;
}

/* ==== LIST MODIFIERS ==== */
int TempleLang::addByte(std::string cname, bool sign) {
	Container *c = new Container();
	
	c->setType(BYTE);
	c->setName(cname);
	c->setSign(sign);
	
	ll->push_back(c);
	return 0;
}

int TempleLang::addWord(std::string cname, bool sign) {
	Container *c = new Container();
	
	c->setType(WORD);
	c->setName(cname);
	c->setSign(sign);
	
	ll->push_back(c);
	return 0;
}

int TempleLang::addDoub(std::string cname, bool sign) {
	Container *c = new Container();
	
	c->setType(DOUB);
	c->setName(cname);
	c->setSign(sign);
	
	ll->push_back(c);
	return 0;
}

int TempleLang::addQuad(std::string cname, bool sign) {
	Container *c = new Container();
	
	c->setType(QUAD);
	c->setName(cname);
	c->setSign(sign);
	
	ll->push_back(c);
	return 0;
}

int TempleLang::generatePython(){
	std::cout << "f = open(\'/path/to/targetFile\')" << std::endl;
	std::list<TempleLang::Container *>::iterator i;
	
	for(i = ll->begin(); i != ll->end(); i++) {
		int size = 0;
		switch((*i)->getType()) {
			case BYTE:
				size = 1;
				break;
			case WORD:
				size = 2;
				break;
			case DOUB:
				size = 4;
				break;
			case QUAD:
				size = 8;
				break;
		}

		std::cout << (*i)->getName() << " = f.read(" << size << ")" << std::endl;
	}

	std::cout << "==========" << std::endl;
	return 0;
}
