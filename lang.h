#include <list>
#include <string>
#include <iostream>

#ifndef LANG_H
#define LANG_H

#define SIGNED		true
#define UNSIGNED	false
#define BYTE 	0x1
#define WORD 	0x2
#define DOUB 	0x3
#define QUAD 	0x4
#define NIBBLE 	0x5
#define STRING 	0x6
#define VLEN 	0x7
#define MAGIC 	0x8
#define BLOB 	0x9
#define SOME 	0xA

class TempleLang {
public:
	TempleLang();
	int addByte(std::string cname, bool sign);
	int addWord(std::string cname, bool sign);
	int addDoub(std::string cname, bool sign);
	int addQuad(std::string cname, bool sign);	
	int generatePython();

protected:
	struct Container {
		int setName(std::string cname);
		std::string getName();
		int setType(int ctype);
		int getType();
		int setSign(bool sign);
		bool getSign();

	private:
		int type;
		bool hasSign;
		std::string name;
		//container(int t,void *o) type(t), obj(o) {}
	};	
public:
	std::list<Container*> *ll;
};
#endif