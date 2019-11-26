#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "proteine.h"
#include "input.h"
#include "sequence.h"
#include "header.h"


using namespace std;




int main() {
	
	map<char,int> conversion;
	conversion['-']=0;
	conversion['A']=1;
	conversion['B']=2;
	conversion['C']=3;
	conversion['D']=4;
	conversion['E']=5;
	conversion['F']=6;
	conversion['G']=7;
	conversion['H']=8;
	conversion['I']=9;
	conversion['J']=27;
	conversion['K']=10;
	conversion['L']=11;
	conversion['M']=12;
	conversion['N']=13;
	conversion['O']=26;
	conversion['P']=14;
	conversion['Q']=15;
	conversion['R']=16;
	conversion['S']=17;
	conversion['T']=18;
	conversion['U']=24;
	conversion['V']=19;
	conversion['W']=20;
	conversion['X']=21;
	conversion['Y']=22;
	conversion['Z']=23;
	conversion['*']=25;
	
	
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
			AAValue.push_back(conversion[ch]); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
			AAValue8.push_back(conversion[ch]); //on stock ces mêmes valeurs de int dans un vecteur qui les transformera directement en binaire		
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

