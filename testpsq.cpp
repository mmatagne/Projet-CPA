#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
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
			cout << ch;
		}
	}
    int8_t i1; //Les int8_t sont des int codés sur 8 bits, donc 1 byte (sizeof(i1) = 1).
    std::ifstream myFile ("P00533.fasta.psq", std::ios::in | std::ios::binary);
    if (!myFile) {
        std::cout << "Error";
    }
    myFile.read((char*) (&i1), sizeof(i1));
    while(myFile.read((char*) (&i1), sizeof(i1))) {
		if((int) i1 == 0) {
			//cout << "New Protein" << endl;
			break;
		}
		//std::cout << (int) i1 << std::endl; //Convertir le int8_t en int est obligatoire pour l'affichage
	}
}
