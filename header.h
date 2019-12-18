#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Header
{	
	private:
	string filename;
	ifstream phr;
	char* title;
	
	public:
	Header(string phrfile);
	~Header();
	char* getTitle(int offset);
	int getID(int offset);

};
#endif
