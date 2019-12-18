/* 

La classe header permet de traiter les fichiers blast .phr contenant le nom ainsi que l'ID des différentes protéines

*/



#include <iostream>
#include <fstream> 
#include "header.h"

using namespace std;

Header::Header(string phrfile) {
	filename = phrfile;
	phr.open(filename, ios::in | ios::binary);
}

Header::~Header(){
	cout << "No probleme header"<< endl;
	phr.close();
}

char* Header::getTitle(int offset) {
	phr.seekg(offset);
	uint8_t var;
	while(phr.read( (char*)(&var), sizeof(var)))
	{
		if(var == 160) //A0 en hex
		{
			phr.read( (char*)(&var), sizeof(var));
			if(var == 128) //80
			{
				phr.read( (char*)(&var), sizeof(var));
				if(var == 26) //1A
				{
					phr.read( (char*)(&var), sizeof(var));
					
					if(var >= 128) //1st bit is a 1 : var(-128 to set 1st bit to 0) = number of bytes on which the length of the title is encoded
					{
						int nbBytes = var-128;
						unsigned long title_length ;
						uint8_t x;
						title_length = 0;
						for (int j = 0; j < nbBytes; j++){ 
							phr.read((char*)&x, 1);
							title_length = title_length << 8 | x; //left shift de 8 cases et OR p/r à la variable x venant d'etre lue
						}
						
						title = new char[title_length+1];
						title[title_length] = '\0';
						phr.read(title, title_length*sizeof(char));
						//cout << title_length << " : " << title << endl;
						return title;
					}
					else // 1st bit is a 0 : var = title_length
					{
						title = new char[var+1];
						title[var] = '\0';
						phr.read(title, var*sizeof(char));
						//cout<< title << endl;
						return title;
					}
				}
			}
		}
	}
}


int Header::getID(int offset) {
	phr.seekg(offset);
	uint8_t var;
	while(phr.read( (char*)(&var), sizeof(var)))
	{
		if(var == 2) //2 aussi en hex
		{
				
			phr.read( (char*)(&var), sizeof(var));
            unsigned long ID;
			uint8_t x;
			ID = 0;
			for (int j = 0; j < var; j++){ 
				phr.read((char*)&x, 1);
				ID = ID << 8 | (unsigned long)x;
			}
			return ID;
		}
	}
	return 0;
}







