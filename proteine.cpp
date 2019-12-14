#include "proteine.h"
#include <iostream>
using std::cout;
using std::endl;

Proteine::Proteine(int new_protNb, int  new_score, forward_list<int> new_listeInconnue, forward_list<int> new_listeDb) {
	protNb = new_protNb;
	score = new_score;
	listeInconnue = new_listeInconnue;
	listeDb = new_listeDb;
}
Proteine::~Proteine(){
	
}


int Proteine::getNb() const{
	return protNb;
}

void Proteine::printResult() {
	
}

