#include "proteine.h"
#include <iostream>
using std::cout;
using std::endl;

Proteine::Proteine(int new_protNb, forward_list<int> new_listeInconnue, forward_list<int> new_listeDb) {
	protNb = new_protNb;
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

