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
}

void Matrice::create_matrice() {
	map<int, char> AA_order;
	map<char, int> AA_conversion = BDDSequences::conversion;
	const string entiers = "-0123456789";
	int res;
	
	ifstream fichier(filename);
	if(fichier.is_open()){
		int k = 0;
		char ch;
		
		while(fichier >> noskipws >> ch) 
		{
			//AA_order[k] = ch;
			
			if(ch == '\n')break;
			if(ch != ' '){
				AA_order[k] = ch;
				cout << AA_order[k] << " " ;
				k++;
			}
			
		}
		cout<<endl;
		
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
					//cout<< stoi(scoreij) << " ";
					j++;
					scoreij="";
				}
			}
			i++; 
			//cout<<endl;
		}
		
		
		/* AFFICHAGE MATRICE POUR VERIFICATION
		for(int i = 0; i<k;i++){
			for(int j = 0; j<k; j++){
				cout<<matrice[i][j]<<" ";
			}
			
		}
		*/
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

