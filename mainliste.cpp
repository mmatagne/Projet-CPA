#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <forward_list>
#include "proteine.h"
#include "input.h"
#include "BDDSequences.h"
#include "sequence.h"
#include "header.h"
#include "matrice.h"


using namespace std;


int getMax(int* array , int array_size){
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

int main(int argc, char **argv) {
	/*if(argc != 3)
	{
		cout << "Seuls 2 arguments sont attendus.\n" << endl;
		return EXIT_FAILURE;
	}
	
	char* a;
	char* b;
	char* c;
	
	a = argv[2];
	b = argv[2];
	c = argv[2];
	
	strcat(a,".pin");
	strcat(b,".psq");
	strcat(c,".phr");
	
	Header phr(c);
	
	
	Input pin(a); 
	pin.readfile();
	cout << pin.getNbSequences() << endl;
	cout << c << endl;
	*/
	
	Input pin("newE.fasta.pin"); 
	pin.readfile();
	Header phr("newE.fasta.phr");
	
	map<char,int> conversion = BDDSequences::getConversionMap();
	
	Matrice matscore("BLOSUM62.txt");
	
	int** blosum = matscore.getMatrice();
	//int blosum[28][28];
	//memcpy(blosum,matscore.matrice,28*28*sizeof(int));
	
	vector<int> AAValue_vector;
	
	//char* protFileName = argv[1];
	
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
			AAValue_vector.push_back(conversion[ch]); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
		}
	}
	
	int sizedb =  __bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()]);
	//BDDSequences sequences(b, sizedb);
	BDDSequences sequences("newE.fasta.psq", sizedb);
	
	

	char* table;
	table = new char[__bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()])];
	table = sequences.getTable();
	int sizeref = AAValue_vector.size();
	
	int* AAValue = &AAValue_vector[0];

	
	int open_pen = 11;
	int ext_pen = 1;
	
	int nbseq = pin.getNbSequences();
	int a;
	int b;
	int score;
	int* scoresvect = new int[nbseq];
	
    for(int k = 0; k < nbseq;k++)
    //for(int k = 2500; k < 3000;k++)
    //for(int k = 5300; k < 5305;k++)
    //2958:6525, 2959:5957
    {	
		
		int sauve = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin.getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin.getSequenceOffsetTable()[k]);
		
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
		
		score = maximum;
		scoresvect[k] = score;
		if (score>2500) cout << "Score : " << k << " "<< score << endl;
		//int sbit = (0.267*score	+ 3.34)/0.69314718056;
		//cout << "Score normalisé " << k << ": " << sbit << endl;
		
	}
	
	//DEBUT DU TRACEBACK 
	
	//création vecteur de Prot
	Proteine* protVect[10];
	int k = 0;
	cout<<"Debut traceback"<<endl;
	for(int iota=0;iota<10;iota++){
		k = getMax(scoresvect, nbseq);
		scoresvect[k]=-1;
		
		// CONSTRUCTION DE MEMO SUR BASE DE L'ALGO
		int sauve = 0;
		int globalmax_i = 0;
		int globalmax_j = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin.getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin.getSequenceOffsetTable()[k]);
		
		int T[sizeref+1] = {};
		
		int max_colonne[sizeref] = {0}; 
		
		int **MEMO = new int*[offsetEnd-offsetBegin+1];
		for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			MEMO[i] = new int[sizeref+1];
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
		}
		
		//DEBUT DU TRACEBACK DANS LA MATRICE MEMO	
		int i = globalmax_i;
		int j = globalmax_j;
		forward_list<int> listeInconnue;
		forward_list<int> listeDb;
		listeInconnue.push_front(AAValue[j]);
		listeDb.push_front(table[offsetBegin+i]);
		
		while(MEMO[i][j] != 0)
		{
			//cout << i << endl;
			//cout << j << endl;
			//cout << MEMO[i][j] << endl;
			if(MEMO[i][j] == 3)
			{
				listeInconnue.push_front(AAValue[j-1]);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
				j -= 1;
			}
			if(MEMO[i][j] == 2)
			{
				listeInconnue.push_front(0);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
			}
			if(MEMO[i][j] == 1)
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
		cout<<"Proteine "<< k << " de score " << maximum << " créée" <<endl;
		
	}
	//int max_index = getMax(scoresvect, nbseq);
	cout << "score : "<< protVect[0]->getNb() << endl;
	delete []scoresvect;
	//cout << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[2958])) << endl;
}


