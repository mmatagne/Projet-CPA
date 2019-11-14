#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

int convertir(char A){
	if(A=='-'){
		return 0;
		}
	if(A=='A'){
		return 1;
		}
	if(A=='B'){
		return 2;
		}
	if(A=='C'){
		return 3;
		}
	if(A=='D'){
		return 4;
		}
	if(A=='E'){
		return 5;
		}
	if(A=='F'){
		return 6;
		}
	if(A=='G'){
		return 7;
		}
	if(A=='H'){
		return 8;
		}
	if(A=='I'){
		return 9;
		}
	if(A=='J'){
		return 27;
		}
	if(A=='K'){
		return 10;
		}
	if(A=='L'){
		return 11;
		}
	if(A=='M'){
		return 12;
		}
	if(A=='N'){
		return 13;
		}
	if(A=='O'){
		return 26;
		}
	if(A=='P'){
		return 14;
		}
	if(A=='Q'){
		return 15;
		}
	if(A=='R'){
		return 16;
		}
	if(A=='S'){
		return 17;
		}
	if(A=='T'){
		return 18;
		}
	if(A=='U'){
		return 24;
		}
	if(A=='V'){
		return 19;
		}
	if(A=='W'){
		return 20;
		}
	if(A=='X'){
		return 21;
		}
	if(A=='Y'){
		return 22;
		}
	if(A=='Z'){
		return 23;
		}
	if(A=='*'){
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
