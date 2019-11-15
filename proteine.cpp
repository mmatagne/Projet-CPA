#include "proteine.h"
#include <iostream>
using std::cout
using std::endl

Proteine::Proteine() : name{""}, data{{}} {
	cout << "Nouvelle proteine" << endl;
}
~Proteine();

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
