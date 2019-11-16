#include "proteine.h"
#include <iostream>
using std::cout;
using std::endl;

Proteine::Proteine(string new_name = "Unknown protein", vector<int> new_data = {}) : name(new_name), data(new_data) {
	cout << "Nouvelle proteine de nom : " << name << endl;
}
Proteine::~Proteine(){
	
}

void Proteine::setName(string new_name){
	name = new_name;
}

void Proteine::setData(vector<int> new_data){
	data = new_data;
}

string Proteine::getName() const{
	return name;
}

vector<int> Proteine::getData() const{
	return data;
}

int Proteine::getLength() const{
	return data.size();
}

bool Proteine::operator==(const Proteine &protDroite) const{
	return data==protDroite.getData();
}


/* fonction main pour tester l'egalite de deux proteines (deux proteines sont egales si elles ont les memes chaines d'acides amines) */ 
int main(){
	
	Proteine prot1("Proteine 1", {2 ,5 ,6} ), prot2("Proteine 2", {2, 5, 6});
	bool var = prot1==prot2;
	cout << var << endl;
}
