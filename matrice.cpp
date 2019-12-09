#include "matrice.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace std;

Matrice::Matrice(string file) {
	filename=file;
}
Matrice::~Matrice(){
}

void Matrice::create_matrice() {
	ifstream fichier(filename);
	if(fichier.is_open()){
		string line;
		int j = 0;
		while(getline(fichier, line) && j<20){
			for(int i = 0; i<20; i++){
				matrice[i][j] = line[i];
			}
			j++; 
		}
		fichier.close();
	}
	else {
		cout << "[Matrice] Impossible d'ouvrir le fichier matrice" << endl;
	}
}

/*
int* Matrice::getMatrice() {
	return matrice;
}
*/
