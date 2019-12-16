#include "BDDSequences.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

BDDSequences::BDDSequences(string db_psqfile, int db_size) {
	table = new char[db_size];
	
	ifstream psq;
	
	psq.open(db_psqfile, ios::in | ios::binary);
	psq.read(table, db_size);
	psq.close();
	int i = 0;
	
	for(int j = 0; j<4; j++){
		i++;
		while((int)table[i])
		{
			i++;
		}
	}
	
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


const map<char,int>& BDDSequences::getConversionMap(){
	return conversion;
}

char* BDDSequences::getTable(){
	return table;
}
