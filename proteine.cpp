#include "proteine.h"
#include "BDDSequences.h"
#include <iostream>
#include <map>
using std::cout;
using std::endl;

map<int, char> conversion = {
	{0,'-'},
	{1,'A'},
	{2,'B'},
	{3,'C'},
	{4,'D'},
	{5,'E'},
	{6,'F'},
	{7,'G'},
	{8,'H'},
	{9,'I'},
	{27,'J'},
	{10,'K'},
	{11,'L'},
	{12,'M'},
	{13,'N'},
	{26,'O'},
	{14,'P'},
	{15,'Q'},
	{16,'R'},
	{17,'S'},
	{18,'T'},
	{24,'U'},
	{19,'V'},
	{20,'W'},
	{21,'X'},
	{22,'Y'},
	{23,'Z'},
	{25,'*'},
};


Proteine::Proteine(int new_protNb, int  new_score, forward_list<int> new_listeInconnue, forward_list<int> new_listeDb) {
	protNb = new_protNb;
	score = new_score;
	listeInconnue = new_listeInconnue;
	listeDb = new_listeDb;
}
Proteine::Proteine(){}

Proteine::~Proteine(){
	
}


int Proteine::getNb() const{
	return protNb;
}

int Proteine::getScore() const{
	return (0.267*score	+ 3.34)/0.69314718056;
}

int Proteine::getRawScore() const{
	return score;
}

void Proteine::printResult() {
	auto it = listeInconnue.begin();
	auto it2 = listeDb.begin();
	int j = 0;
	
	
	while(it != listeInconnue.end())
	{
		cout << "Query: ";
		for(int i = 0; i<60; ++i)
		{
			cout << conversion[*it];
			it++;
			if(it == listeInconnue.end())
			{
				break;
			}
		}
		cout << endl;
		cout << "Sbjct: ";
		for(int i = 0; i<60; ++i)
		{
			cout << conversion[*it2];
			it2++;
			if(it2 == listeInconnue.end())
			{
				break;
			}
		}
		cout << endl;
		cout << endl;
	}
}
//

