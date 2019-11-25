#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "proteine.h"
#include "input.h"


using namespace std;

int convertir(char A){
	
	switch(A){
		
		case '-':
			return 0;
			
		case 'A':
			return 1;
			
		case 'B':
			return 2;
			
		case 'C':
			return 3;
			
		case 'D':
			return 4;
			
		case 'E':
			return 5;
			
		case 'F':
			return 6;
			
		case 'G':
			return 7;
			
		case 'H':
			return 8;
			
		case 'I':
			return 9;
			
		case 'J':
			return 27;
			
		case 'K':
			return 10;
			
		case 'L':
			return 11;
			
		case 'M':
			return 12;
			
		case 'N':
			return 13;
			
		case 'O':
			return 26;
			
		case 'P':
			return 14;
			
		case 'Q':
			return 15;
			
		case 'R':
			return 16;
			
		case 'S':
			return 17;
			
		case 'T':
			return 18;
			
		case 'U':
			return 24;
			
		case 'V':
			return 19;
			
		case 'W':
			return 20;
			
		case 'X':
			return 21;
			
		case 'Y':
			return 22;
			
		case 'Z':
			return 23;
			
		case '*':
			return 25;
	}
	return 0;
}


int main() {
	ifstream header("uniprot_sprot.fasta.phr", ios::in | ios::binary);
	 
	char* title2;
	Input pin("uniprot_sprot.fasta.pin"); 
	pin.readfile();
	
	vector<int> AAValue;
	vector<int8_t> AAValue8; 
	
	ifstream protFile ("P00533.fasta");
	if (!protFile) 
	{
		cout << "Error" << endl;
	}
	string firstLine;
	getline(protFile,firstLine);
	char ch;
	while(protFile >> noskipws >> ch) 
	{
		if(ch != '\n') 
		{
			AAValue.push_back(convertir(ch)); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
			AAValue8.push_back(convertir(ch)); //on stock ces mêmes valeurs de int dans un vecteur qui les transformera directement en binaire		
		}
	}
	for (int i = 0; i < AAValue.size(); i++) {  //on imprime tous les int contenus dans le vecteur
		//cout << AAValue.at(i) << ' ';
	}
	
	for (int i = 0; i < AAValue8.size(); i++) {  //imprime les éléments du vecteur binaire
		//cout << AAValue8.at(i);
		
	}
	Proteine protref("Inconnu",AAValue);
	
	
	int nbSequences = pin.getNbSequences();
	
    int8_t i1; //Les int8_t sont des int codés sur 8 bits, donc 1 byte (sizeof(i1) = 1).
    std::ifstream psqFile ("uniprot_sprot.fasta.psq", std::ios::in | std::ios::binary);
    psqFile.read((char*) (&i1), sizeof(i1));
    for(int i2 = 0; i2 < nbSequences;i2++)
    {	
		header.seekg(__bswap_32(pin.getHeaderOffsetTable()[i2]));
		int8_t var;
		while(header.read( (char*)(&var), sizeof(var)))
		{
			//cout << hex << (unsigned int)(unsigned char) var << endl;
			if((unsigned int)(unsigned char) var == 160) //A0 en hex
			{
				int8_t var2;
				header.read( (char*)(&var2), sizeof(var2));
				//cout << hex << (unsigned int)(unsigned char) var2 << endl;
				if((unsigned int)(unsigned char) var2 == 128) //80
				{
					int8_t var3;
					header.read( (char*)(&var3), sizeof(var3));
					//cout << hex << (unsigned int)(unsigned char) var3 << endl;
					if((unsigned int)(unsigned char) var3 == 26) //1A
					{
						int8_t var4;
						header.read( (char*)(&var4), sizeof(var4));
						//cout << hex << (unsigned int)(unsigned char) var4 << endl;
						//if((unsigned int)(unsigned char) var4 > 128) 
						//{
							//int nbBytes = var4-128;
							
						//}
						if((unsigned int)(unsigned char) var4 > 128)
						{
							//cout << "Trop long" << endl;
							//title2 = new char[81];
							//header.read(title2, var4);
							//cout << title2 << endl;
							break;
						}
						else {
							title2 = new char[var4];
							header.read(title2, var4);
							//cout << title2 << endl;
							break;
						}
					}
				}
			}
		}
		Proteine prot("currentprot",{});
		vector<int> data; 
		while(psqFile.read((char*) (&i1), sizeof(i1))) {
			if((int) i1 == 0) 
			{
				prot.setData(data);
				if(prot==protref)
				{
					prot.setName(title2);
					cout << title2 << endl;
					return 0;
				}
				break;
			}
			data.push_back((int)i1);
		}
	}
}
