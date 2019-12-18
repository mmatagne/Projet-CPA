/* La classe Matrice permet de créer une matrice à partir d'un fichier texte contenant une matrice blossum. */

#include "matrice.h"
#include "BDDSequences.h"
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
	matrice = new int*[28]; //quel que soit la taille de la blossum, la matrice créée sera toujours de taille 28*28
	for(int l = 0; l<28; l++) matrice[l]=new int[28]();
	const string entiers = "-0123456789";
	int res;
	
	ifstream fichier(filename);
	if(fichier.is_open()){
		int k = 0;
		char ch;
		
		while(fichier >> noskipws >> ch) 
		{

			if(ch == '\n')break;
			if(ch != ' '){
				AA_order[k] = ch;
				k++;
			}
			
		}
		
		string line;
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
		
		
		/* AFFICHAGE DE LA MATRICE LUE
		for(int i = 0; i<k;i++){
			for(int j = 0; j<k; j++){
				string espace = "";
				if(matrice[i][j]>=0) espace+=" ";
				if(matrice[i][j]-10 <= 0) espace+=" ";
				cout<<espace<<matrice[i][j];
				
			}
			cout<<endl;

		}
		*/
		
		fichier.close();
	}
	else {
		cout << "[Matrice] Impossible d'ouvrir le fichier matrice" << endl;
	}

}


int** Matrice::getMatrice() const{
	return matrice;
}


