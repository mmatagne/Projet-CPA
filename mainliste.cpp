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
	
	map<char,int> conversion;
	conversion['-']=0;
	conversion['A']=1;
	conversion['B']=2;
	conversion['C']=3;
	conversion['D']=4;
	conversion['E']=5;
	conversion['F']=6;
	conversion['G']=7;
	conversion['H']=8;
	conversion['I']=9;
	conversion['J']=27;
	conversion['K']=10;
	conversion['L']=11;
	conversion['M']=12;
	conversion['N']=13;
	conversion['O']=26;
	conversion['P']=14;
	conversion['Q']=15;
	conversion['R']=16;
	conversion['S']=17;
	conversion['T']=18;
	conversion['U']=24;
	conversion['V']=19;
	conversion['W']=20;
	conversion['X']=21;
	conversion['Y']=22;
	conversion['Z']=23;
	conversion['*']=25;
	
	
	
	Matrice matscore("BLOSUM62.txt");
	int blosum[28][28];
	memcpy(blosum,matscore.matrice,28*28*sizeof(int));
	
	
	//Matrice matscore(argv...);
	//blosum = matscore.getMatrice();
	//blosum = [...................] Déclarer la matrice BLOSUM ici.
	
	vector<int> AAValue_vector;
	
	char* protFileName = argv[1];
	
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
	

	//Proteine protref("Inconnu",AAValue);

	
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
	int score_min = 0;
	
	//création vecteur de Prot
	vector<Proteine*> protVect;
	int size_vect = 0; //Nombre de proténies présentes dans le vecteur
	
	int count = 0;
	int sauve = 0;
	
	int nbseq = pin.getNbSequences();
	int a;
	int b;
	
	vector<int> scoresvect;
	
    for(int k = 0; k < nbseq;k++)
    //for(int k = 2958; k < 2959;k++)
    //2958:6525, 2959:5957
    {	
		int globalmax_i = 0;
		int globalmax_j = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin.getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin.getSequenceOffsetTable()[k]);
		
		int T[sizeref+1] = {};
		
		int max_colonne[sizeref] = {0}; 
		
		//int **MEMO = new int*[offsetEnd-offsetBegin+1];
		//for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			//MEMO[i] = new int[sizeref+1];
		//}
		
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
					//MEMO[i][j] = 0;
				}
				
				else if (a < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] && b < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]])
				{
					value = sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]];
					//MEMO[i][j] = 1;
				}
				
				else if (a < b)
				{
					value = b;
					//MEMO[i][j] = 2;
				}
				else
				{
					value = a;
					//MEMO[i][j] = 3;
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
		
		int score = maximum;
		//cout << "Score : " << score << endl;
		scoresvect.push_back(score);
		int sbit = (0.267*score	+ 3.34)/0.69314718056;
		//cout << "Score normalisé : " << sbit << endl;
		
		/*
		if(score > score_min) //cas où on doit faire le traceback
		{
			count++;
			//cout << score_min << endl;
			//cout << count << endl;
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
					i = i - 1;
					j = j - 1;
				}
				if(MEMO[i][j] == 2)
				{
					listeInconnue.push_front(0);
					listeDb.push_front(table[offsetBegin+i-1]);
					i = i - 1;
				}
				if(MEMO[i][j] == 1)
				{
					listeInconnue.push_front(AAValue[j-1]);
					listeDb.push_front(0);
					j = j - 1;
				}
			}

			Proteine* prot = new Proteine(k,score,listeInconnue,listeDb);
			if (size_vect < 10)
			{
				protVect.push_back(prot);
				size_vect++;
			}
			else if (size_vect == 10)
			{
				int newmin = protVect[0]->getScore();
				int todelete = 0;
				for(int i = 0; i < 10; i++)
				{
					if(protVect[i]->getScore() < newmin)
					{
						newmin = protVect[i]->getScore();
						todelete = i;
					}
				}
				protVect.erase(protVect.begin() + todelete);
				protVect.push_back(prot);
				int min = 1000000;
				for(int i = 0; i < 10; i++)
				{
					if(protVect[i]->getScore() < min)
					{
						min = protVect[i]->getScore();
					}
				}
				score_min = min;
			}
		}*/
		/*for(int i = 0; i < offsetEnd-offsetBegin; ++i) {
			delete [] M[i];
		}
		delete [] M;*/
		//for(int i = 0; i < offsetEnd-offsetBegin; ++i) {
			//delete [] MEMO[i];
		//}
		//delete [] MEMO;
	}
	//cout << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[2958])) << endl;
}


