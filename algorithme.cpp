#include <iostream>
#include "algorithme.h"
using namespace std;

Algorithme::Algorithme(Input* input, BDDSequences* bddsequences, vector<int>* query_prot, int** mat, int o_p, int ext_p)
{
	//cout<< "pret à lancer algo" << endl;
	pin = input;
	sequences = bddsequences;
	open_pen = o_p;
	ext_pen = ext_p;
	sizeref = (*query_prot).size();
	blosum = mat;
	AAValue = query_prot->data();
	
	scoresvect = new int[pin->getNbSequences()];
	//cout << "Algorithme initialise "<< AAValue[0] << endl;
	
}

Algorithme::~Algorithme(){
	
	//delete [] scoresvect;
	
	cout << "No probleme algo"<< endl;
}

int Algorithme::getMax(int* array , int array_size){
	int index_of_max = 0;
	for(int i=0; i<array_size; i++){
		if(array[i]>array[index_of_max]) {
			index_of_max = i;
			//cout<<"New max found " <<index_of_max << endl;
		}
	}
	//cout<< "Index of max : " << index_of_max  << endl;
	return index_of_max;
}

int* Algorithme::getScoresTable(){
	return scoresvect;
}
	
void Algorithme::run(){
	
	char* table = sequences->getTable();
	
	int nbseq = pin->getNbSequences();
	int a;
	int b;
	
    for(int k = 0; k < nbseq;k++)
    //for(int k = 2950; k < 3000;k++)
    //for(int k = 5300; k < 5305;k++)
    //2958:6525, 2959:5957
    {	
		
		int sauve = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin->getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin->getSequenceOffsetTable()[k]);
		
		int T[sizeref+1] = {};
		
		int max_colonne[sizeref] = {0}; 
		
		for(int i = 1; i < offsetEnd-offsetBegin; i++)
		{
			int max_ligne = 0;
			for (int j = 1; j < sizeref+1;j++)
			{
				
					
				if(T[j]-open_pen < max_colonne[j-1]-ext_pen)
				{
					
					a = max_colonne[j-1]-ext_pen;
				}
				
				else
				{
					a = T[j]-open_pen;
					max_colonne[j-1] = a;
				}
				
				max_colonne[j-1] = max_colonne[j-1] - ext_pen;
				
				
				if(T[j-1]-open_pen < max_ligne-ext_pen)
				{
					b = max_ligne-ext_pen;
				}
				
				else
				{
					b = T[j-1]-open_pen;
					max_ligne = b;
				}
				
				max_ligne = max_ligne - ext_pen;
				
				int value;
				//cout << table[offsetBegin+i-1] << endl;
				//cout << j << endl;
				//cout << AAValue[j-1] << endl;
				//cout<< "algorithme lancé "<< blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]]<< endl;
				
				if(sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] < 0 && a < 0 && b < 0)
				{
					value = 0;
					
				}
				
				else if (a < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] && b < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]])
				{
					value = sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]];
				}
				
				else if (a < b)
				{
					value = b;
				}
				else
				{
					value = a;
				}
				
				sauve = T[j];
				T[j] = value;
				
				if(maximum < value)
				{
					maximum = value;
				}
			}
		}
		
		scoresvect[k] = maximum;
		
		//if (score>2500) cout << "Score : " << k << " "<< score << endl;
		//int sbit = (0.267*score	+ 3.34)/0.69314718056;
		//cout << "Score normalisé " << k << ": " << sbit << endl;
		
	}
}

Proteine** Algorithme::getAlignment(int nb_prot)
{
	//DEBUT DU TRACEBACK 
	
	//création vecteur de Prot
	protVect = new Proteine*[nb_prot];
	int k = 0;
	int a;
	int b;
	char* table = sequences->getTable();
	int nbseq = pin->getNbSequences();
	
	for(int iota=0;iota<nb_prot;iota++){
		k = getMax(scoresvect, nbseq);
		scoresvect[k]=-1;
		
		// CONSTRUCTION DE MEMO SUR BASE DE L'ALGO
		int sauve = 0;
		int globalmax_i = 0;
		int globalmax_j = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin->getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin->getSequenceOffsetTable()[k]);
		
		int T[sizeref+1] = {};
		
		int max_colonne[sizeref] = {0}; 
		
		int **MEMO = new int*[offsetEnd-offsetBegin+1];
		for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			MEMO[i] = new int[sizeref+1];
		}
		
		for(int i = 0; i < offsetEnd-offsetBegin+1; ++i)
		{
			MEMO[i][0] = 0;
		}
		
		for(int j = 0; j < sizeref+1; ++j)
		{
			MEMO[0][j] = 0;
		}
		
		for(int i = 1; i < offsetEnd-offsetBegin; i++)
		{
			int max_ligne = 0;
			for (int j = 1; j < sizeref+1;j++)
			{
				
					
				if(T[j]-open_pen < max_colonne[j-1]-ext_pen)
				{
					a = max_colonne[j-1]-ext_pen;
				}
				
				else
				{
					a = T[j]-open_pen;
					max_colonne[j-1] = a;
				}
				
				max_colonne[j-1] = max_colonne[j-1] - ext_pen;
				
				if(T[j-1]-open_pen < max_ligne-ext_pen)
				{
					b = max_ligne-ext_pen;
				}
				
				else
				{
					b = T[j-1]-open_pen;
					max_ligne = b;
				}
				
				max_ligne = max_ligne - ext_pen;
				
				int value;
				
				if(sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] < 0 && a < 0 && b < 0)
				{
					value = 0;
					MEMO[i][j] = 0;
				}
				
				else if (a < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] && b < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]])
				{
					value = sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]];
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
				sauve = T[j];
				T[j] = value;
				
				if(maximum < value)
				{
					maximum = value;
					globalmax_i = i;
					globalmax_j = j;
				}
			}
			//cout << maximum << endl;
		}
		
		//DEBUT DU TRACEBACK DANS LA MATRICE MEMO	
		int i = globalmax_i;
		int j = globalmax_j;
		forward_list<int> listeInconnue;
		forward_list<int> listeDb;
		//listeInconnue.push_front(AAValue[j-1]);
		//listeDb.push_front(table[offsetBegin+i]);
		//cout << i << endl;
		//cout << j << endl;
		while(MEMO[i][j] != 0)
		{
			//cout << i << endl;
			//cout << j << endl;
			//cout << MEMO[i][j] << endl;
			if(MEMO[i][j] == 1)
			{
				listeInconnue.push_front(AAValue[j-1]);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
				j -= 1;
			}
			if(MEMO[i][j] == 3)
			{
				listeInconnue.push_front(0);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
			}
			if(MEMO[i][j] == 2)
			{
				listeInconnue.push_front(AAValue[j-1]);
				listeDb.push_front(0);
				j -= 1;
			}
		}

		for(int i = 0; i < offsetEnd-offsetBegin; ++i) {
			delete [] MEMO[i];
		}
		delete [] MEMO;
		protVect[iota] = new Proteine(k,maximum,listeInconnue,listeDb);
		//cout<<"Proteine "<< k << " de score " << maximum << " créée" <<endl;	
	}
	return protVect;
}

//
