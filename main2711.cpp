#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "proteine.h"
#include "input.h"
#include "BDDSequences.h"
#include "sequence.h"
#include "header.h"


using namespace std;




int main() {
	ifstream header("uniprot_sprot.fasta.phr", ios::in | ios::binary);
	Header phr("uniprot_sprot.fasta.phr");
	
	
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
	
	int sizedb =  __bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()]);
	BDDSequences sequences("uniprot_sprot.fasta.psq", sizedb);
	
	char* table;
	table = new char[__bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()])];
	table = sequences.getTable();
	int sizeref = AAValue.size();
	int trouve=0;
	
    for(int i = 0; i < pin.getNbSequences()-1;i++)
    {	
		if(trouve==1) 
		{
			break;
		}
		for(int j = __bswap_32(pin.getSequenceOffsetTable()[i]); j < __bswap_32(pin.getSequenceOffsetTable()[i+1]); j++)
		{
			if(j - __bswap_32(pin.getSequenceOffsetTable()[i]) >= sizeref)
			{
				break;
			}
			if((int8_t)table[j] == AAValue[j - __bswap_32(pin.getSequenceOffsetTable()[i])])
			{
				if(j - __bswap_32(pin.getSequenceOffsetTable()[i]) == sizeref - 1)
				{
					cout << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[i])) << endl;
					trouve=1;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}
