#include "BDDSequences.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

BDDSequences::BDDSequences(string db_psqfile, int db_size) {
	table = new char[db_size];
	
	cout << "Memory allocated : " << db_size << "bytes"<< endl;
	ifstream psq;
	
	psq.open(db_psqfile, ios::in | ios::binary);
	psq.read(table, db_size);
	psq.close();
	//cout << "Sequences added to memory" << endl;
	int i = 0;
	//cout << (int)table[i] << endl;
	
	for(int j = 0; j<4; j++){
		i++;
		//cout << (int)table[i] << endl;
		while((int)table[i])
		{
			
		//cout << (int)table[i] << " " ;
			i++;
		}
	}
	
	/*
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
	*/
}
BDDSequences::~BDDSequences(){
	delete table;
}
const map<char, int> BDDSequences::conversion = {
	{'-', 0 },
	{'A', 1 },
	{'B', 2 },
	{'C', 3 },
	{'D', 4 },
	{'E', 5 },
	{'F', 6 },
	{'G', 7 },
	{'H', 8 },
	{'I', 9 },
	{'J', 27 },
	{'K', 10 },
	{'L', 11 },
	{'M', 12 },
	{'N', 13 },
	{'O', 26 },
	{'P', 14 },
	{'Q', 15 },
	{'R', 16 },
	{'S', 17 },
	{'T', 18 },
	{'U', 24 },
	{'V', 19 },
	{'W', 20 },
	{'X', 21 },
	{'Y', 22 },
	{'Z', 23 },
	{'*', 25 },
};

/*
const static map<char,int> BDDSequences::getConversionMap() const{
	return conversion;
}
*/
char* BDDSequences::getTable(){
	return table;
}
