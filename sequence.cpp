/* La classe sequence permet de récupérer la séquence d'acides aminés depuis le fichier blast .psq */

#include "sequence.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

Sequence::Sequence(string psqfile) {
	filename = psqfile;
	psq.open(filename, ios::in | ios::binary);
	int8_t i1;
	psq.read((char*) (&i1), sizeof(i1));
}
Sequence::~Sequence(){
	
}

vector<int> Sequence:: getSequence(){   //getSequence renvoie un vecteur d'entiers correspondant aux acides aminés
	vector<int> data;
	int8_t i1;
	while(psq.read((char*) (&i1), sizeof(i1))) {
		if((int) i1 == 0) 
		{
			return data;
		}
		data.push_back((int)i1);
	}
	return data;
}

