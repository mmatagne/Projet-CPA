#include <iostream>
#include <fstream> 
#include "header.h"

using namespace std;

Header::Header(string phrfile) {
	filename = phrfile;
	phr.open(filename, ios::in | ios::binary);
}

Header::~Header(){
	phr.close();
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
						int nbBytes = (unsigned int)(unsigned char)var4-128;
						unsigned long intFound ;
						int8_t x;
						intFound = 0;
						for (int j = 0; j < nbBytes; j++){ 
							phr.read((char*)&x, 1);
							intFound = intFound << 8 | (unsigned int)(unsigned char)x; //left shift de 8 cases et OR p/r à la variable x venant d'etre lue
						}
						//cout << intFound << endl;
						title2 = new char[intFound];
						phr.read(title2, intFound);
						cout << title2 << endl;
						return title2;
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

