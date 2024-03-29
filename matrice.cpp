#include "matrice.h"
#include "BDDSequences.h"
/* La classe Matrice permet de créer une matrice à partir d'un fichier 
 * texte contenant une matrice blosum. */

#include <iostream>
#include <map>
using std::cout;
using std::endl;
using namespace std;

Matrice::Matrice(string file) {
	filename=file;
	create_matrice();
}
Matrice::~Matrice(){
	
	for(int i = 0; i<28; i++){
		delete[] matrice[i];
	}
	delete[] matrice;
	
}

void Matrice::create_matrice() {
	map<int, char> AA_order;
	map<char, int> AA_conversion = BDDSequences::getConversionMap();
	matrice = new int*[28]; //quelle que soit la taille de la blossum, la matrice créée sera toujours de taille 28*28
	for(int l = 0; l<28; l++) matrice[l]=new int[28]();
	const string entiers = "-0123456789";
	int res;
	
	ifstream fichier(filename);
	if(fichier.is_open()){
		string line;
		int k = 0;
		char ch;
		while(fichier >> noskipws >> ch) 
		{
			if(ch == '#') getline(fichier, line);
			else if(ch == '\n')break;
			else if(ch != ' '){
				AA_order[k] = ch;
				k++;
			}
			
		}
		
		int i = 0;
		
		while(getline(fichier, line)  && i < k){
			string scoreij = "";
			int j = 0;
			for(char &c : line){
				if((res = entiers.find(c))>=0){
					scoreij += c;
				}else if(scoreij != ""){
					matrice[AA_conversion[AA_order[i]]][AA_conversion[AA_order[j]]] = stoi(scoreij);
					j++;
					scoreij="";
				}
			}
			i++; 
		}
		fichier.close();
	}
	else {
		cout << "[Matrice] Impossible d'ouvrir le fichier matrice" << endl;
	}

}


int** Matrice::getMatrice() const{
	return matrice;
}


