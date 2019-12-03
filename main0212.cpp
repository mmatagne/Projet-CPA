#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "proteine.h"
#include "input.h"
#include "BDDSequences.h"
#include "sequence.h"
#include "header.h"


using namespace std;




int main() {
	ifstream header("uniprot_sprot.fasta.phr", ios::in | ios::binary);
	Header phr("uniprot_sprot.fasta.phr");
	
	
	Input pin("uniprot_sprot.fasta.pin"); 
	pin.readfile();
	
	//blosum = [...................] Déclarer la matrice BLOSUM ici.
	
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
			AAValue.push_back(conversion[ch]); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
			AAValue8.push_back(conversion[ch]); //on stock ces mêmes valeurs de int dans un vecteur qui les transformera directement en binaire		
		}
	}

	Proteine protref("Inconnu",AAValue);
	
	int sizedb =  __bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()]);
	BDDSequences sequences("uniprot_sprot.fasta.psq", sizedb);
	
	char* table;
	table = new char[__bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()])];
	table = sequences.getTable();
	int sizeref = AAValue.size();
	int trouve=0;
	
	/*Jusqu'ici c'est comme avant j'ai rien touché.
	 * table c'est notre fichier psq copié.
	 * 
	 * J'ai suivi exactement l'algorithme de la page Wikipedia qui s'appelle
	 * "Algorithme de Smith-Waterman".
	 * blosum correspond à la matrice des scores de correspondance. En gros
	 * c'est la matrice D qu'ils mentionnent parfois dans le Wikipedia 
	 * (regardez l'exemple en dessous de l'algo sur Wikipedia ils parlent de 
	 * la matrice BLOSUM62 qu'ils ont utilisé.
	 * Cette matrice blosum c'est pas encore initialisée dans ce code, ce qui
	 * fait que celui-ci n'est pas exécutable, et ne compile pas.
	 * 
	 * Pour le fonctionnement de l'algo :
	 * -on a une matrice M à remplir, comme dans l'exemple Wiki. 
	 * Pour la remplir, on doit prendre le maximum entre les 4 possibilités
	 * présentées sur Wikipedia (0, M(i-1,j-1)+D(Ai,Bj), M(i-1,j)+delta, M(i,j-1)+delta.
	 * Ce delta correspond à la variable penalite dans ce code (mise à -3 mais on peut changer). 
	 * 
	 * -l'élément 0,0 de cette matrice (en haut à gauche) vient forcément
	 * de la blosum car on a pas d'éléments à gauche ni en haut (on ne peut pas 
	 * faire i-1 ou j-1 car on sortirait de la matrice).
	 * 
	 * -on parcourt toutes les séquences de la database (k),
	 * on parcourt touts les acides aminés de la séquence "du moment" 
	 * de la database (j), et on parcourt tous les acides aminés de la 
	 * séquence inconnue (i). On a bien un triple for avec k, j, et i.
	 * 
	 * -Pour chaque élément, on trouve le maximum entre les 4 propositions 
	 * dont on a parlées avant. C'est la fonction getMax qui s'en occupe.
	 *
	 * Ce qu'il faut encore faire :
	 * -écrire la matrice blosum dans ce code (choisir par exemple la BLOSUM62 
	 * sur Internet).
	 * 
	 * -rajouter une première ligne et une première colonne vide à la matrice
	 * M pour éviter d'avoir des erreurs (et donc écrire M[1,1] à la ligne 105 
	 * au lieu de M[0][0]. 
	 * 
	 * -faire l'étape de "trace_back" pour retrouver le meilleur alignement
	 * une fois qu'on a fini de faire la matrice M. 
	*/ 
	
	int open_pen = 11;
	int ext_pen = 1;
	
    for(int k = 0; k < pin.getNbSequences()-1;k++)
    {	
		int globalmax_i, globalmax_j;
		int offsetEnd = __bswap_32(pin.getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin.getSequenceOffsetTable()[k]);
		int M[offsetEnd - offsetBegin +1][sizeref +1];
		int MEMO[offsetEnd - offsetBegin +1][sizeref +1];
		//M[1][1] = blosum[table[__bswap_32(pin.getSequenceOffsetTable()[k])],AAValue[0]];
		for(int i = 0; i < offsetEnd - offsetBegin +1;i++)
		{
			M[i][0] = 0;
		}
		for(int j = 0; j < sizeref +1;j++)
		{
			M[0][j] = 0;
		}
		
		int[offsetEnd-offsetBegin] max_colonne = {0}; //Attention on commence bien à 0 ici pour la premiere colonne de la matrice.
		
		for(int i = 1; i < offsetEnd-offsetBegin +1; i++)
		{
			int max_ligne = 0;
			for (int j = 1; i < sizeref+1; i++)
			{
				int a;
				if(M[i-1][j]-open_pen < max_colonne[j-1]-ext_pen)
				{
					a = max_colonne[j-1]-ext_pen;
				}
				else
				{
					a = M[i-1][j]-open_pen;
					max_colonne[j-1] = a;
				}
					
				int b;
				if(M[i][j-1]-open_pen < max_ligne-ext_pen)
				{
					b = max_ligne-ext_pen;
				}
				else
				{
					b = M[i][j-1]-open_pen;
					max_ligne = b;
				}
				
				int value;
				
				if(M[i-1][j-1] + blosum[table[offsetBegin+i],AAValue[j]] < 0 && a < 0 && b < 0)
				{
					value = 0;
					MEMO[i][j] = 0;
				}
				else if (a < M[i-1][j-1] + blosum[table[offsetBegin+i],AAValue[j]] && n < M[i-1][j-1] + blosum[table[offsetBegin+i],AAValue[j]])
				{
					value = M[i-1][j-1] + blosum[table[offsetBegin+i],AAValue[j]];
					MEMO[i][j] = 1;
				}
				else if (a < b)
				{
					value = b;
					MEMO[i][j] = 2;
				}
				else
				{
					value = a;
					MEMO[i][j] = 3;
				}
				M[i][j] = value;
				if(M[globalmax_i][globalmax_j] < value)
				{
					globalmax_i = i;
					globalmax_j = j;
				}
			}
		}
		int score = M[globalmax_i][globalmax_j];
	}
}

int getMax(int* M,int* MEMO,int a, int b) //max(0,M[i-1][j-1] + blosum[table[i],AAValue[j]],M[i-1][j] + penalite,M[i][j-1] + penalite)
{
	if(M[i-1][j-1] + blosum[table[i],AAValue[j]] < 0 && a < 0 && b < 0)
	{
		MEMO[i][j] = 0;
		return 0
	}
	else if (a < M[i-1][j-1] + blosum[table[i],AAValue[j]] && n < M[i-1][j-1] + blosum[table[i],AAValue[j]])
	{
		MEMO[i][j] = 1;
		return M[i-1][j-1] + blosum[table[i],AAValue[j]];
	}
	else if (a < b)
	{
		MEMO[i][j] = 2;
		return b;
	}
	else
	{
		MEMO[i][j] = 3;
		return a;
	}
}

	
	
	
	
	
	
