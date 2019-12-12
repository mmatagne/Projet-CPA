#include <iostream>
#include <fstream> 
#include "header.h"

using namespace std;

Header::Header(string phrfile) {
	filename = phrfile;
	phr.open(filename, ios::in | ios::binary);
}

Header::~Header(){
	
}

char* Header::getTitle(int offset) {
	phr.seekg(offset);
	int8_t var;
	while(phr.read( (char*)(&var), sizeof(var)))
	{
		if((unsigned int)(unsigned char) var == 160) //A0 en hex
		{
			int8_t var2;
			phr.read( (char*)(&var2), sizeof(var2));
			if((unsigned int)(unsigned char) var2 == 128) //80
			{
				int8_t var3;
				phr.read( (char*)(&var3), sizeof(var3));
				if((unsigned int)(unsigned char) var3 == 26) //1A
				{
					int8_t var4;
					phr.read( (char*)(&var4), sizeof(var4));
					if((unsigned int)(unsigned char) var4 > 128)
					{
						break;
					}
					else {
						title2 = new char[var4];
						phr.read(title2, var4);
						return title2;
					}
				}
			}
		}
	}
}

