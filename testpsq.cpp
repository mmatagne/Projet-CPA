#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

int convertir(char A){
	
	switch(A){
		
		case '-':
			return 0;
			
		case 'A':
			return 1;
			
		case 'B':
			return 2;
			
		case 'C':
			return 3;
			
		case 'D':
			return 4;
			
		case 'E':
			return 5;
			
		case 'F':
			return 6;
			
		case 'G':
			return 7;
			
		case 'H':
			return 8;
			
		case 'I':
			return 9;
			
		case 'J':
			return 27;
			
		case 'K':
			return 10;
			
		case 'L':
			return 11;
			
		case 'M':
			return 12;
			
		case 'N':
			return 13;
			
		case 'O':
			return 26;
			
		case 'P':
			return 14;
			
		case 'Q':
			return 15;
			
		case 'R':
			return 16;
			
		case 'S':
			return 17;
			
		case 'T':
			return 18;
			
		case 'U':
			return 24;
			
		case 'V':
			return 19;
			
		case 'W':
			return 20;
			
		case 'X':
			return 21;
			
		case 'Y':
			return 22;
			
		case 'Z':
			return 23;
			
		case '*':
			return 25;
		

	
	}

}


int main() {
	
	vector<int> AAValue;
	vector<int8_t> AAValue8; 
	
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
			AAValue.push_back(convertir(ch)); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
			AAValue8.push_back(convertir(ch)); //on stock ces mêmes valeurs de int dans un vecteur qui les transformera directement en binaire		
		}
	}
	for (int i = 0; i < AAValue.size(); i++) {  //on imprime tous les int contenus dans le vecteur
		cout << AAValue.at(i) << ' ';
		
	}
	
	for (int i = 0; i < AAValue8.size(); i++) {  //imprime les éléments du vecteur binaire
		cout << AAValue8.at(i);
		
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
