#include "bddsequences.h"
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
	//for (int i = 0; i< 20; i++) cout << (int) table[i] << endl;
	
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
}
BDDSequences::~BDDSequences(){
	delete table;
}

char* BDDSequences::getTable(){
	return table;
}




