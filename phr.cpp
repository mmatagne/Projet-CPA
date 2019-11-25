#include <iostream>
#include <fstream> 
#include "phr.h"

using namespace std;

Phr::Phr(string phrfile) {
	filename = phrfile;
}

Phr::~Phr(){
	
}

void Phr::readfile() {
	ifstream fichier(filename, ios::in | ios::binary);
	if(fichier.is_open())
	{
		for(int i=0;i<100;i++) 
		{
			int8_t version;
			fichier.read( (char*)(&version), sizeof(version));  
			//cout << hex << (unsigned int)(unsigned char) version << endl;
		}
	}
	
}

