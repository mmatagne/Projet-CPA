#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "proteine.h"
#include "input.h"
#include "sequence.h"
#include "header.h"


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
	//ifstream header("uniprot_sprot.fasta.phr", ios::in | ios::binary);
	Header phr("uniprot_sprot.fasta.phr");
	 
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

	Proteine protref("Inconnu",AAValue);
	
    Sequence psq("uniprot_sprot.fasta.psq");
    for(int i2 = 0; i2 < pin.getNbSequences();i2++)
    {	
		title2 = phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[i2]));
		Proteine prot("currentprot",{});
		vector<int> data;
		data = psq.getSequence();
		
		prot.setData(data);
		if(prot==protref)
		{
			prot.setName(title2);
			cout << title2 << endl;
			return 0;
		}
	}
}

