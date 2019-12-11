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
	
	
	/*int blosum[27][27] = {
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	0,1,5,4,2,4,1,0,9,7,0,8,6,8,0,0,8,5,3,1,9,1,0,9,8,9,5,
	};*/
	
	Matrice matscore("BLOSUM62.txt");
	int blosum[28][28];
	memcpy(blosum,matscore.matrice,28*28*sizeof(int));
	
	
	//Matrice matscore(argv...);
	//blosum = matscore.getMatrice();
	//blosum = [...................] Déclarer la matrice BLOSUM ici.
	
	vector<int> AAValue;
	vector<int8_t> AAValue8; 
	
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
			AAValue.push_back(conversion[ch]); //on stock toutes les valeurs de int correspondant aux char dans un vecteur AAValue
		}
	}

	//Proteine protref("Inconnu",AAValue);

	
	int sizedb =  __bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()]);
	//BDDSequences sequences(b, sizedb);
	BDDSequences sequences("newE.fasta.psq", sizedb);
	
	

	char* table;
	table = new char[__bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()])];
	table = sequences.getTable();
	int sizeref = AAValue.size();
	
	int open_pen = 11;
	int ext_pen = 1;
	int score_min = 0;
	
	//création vecteur de Prot
	vector<Proteine*> protVect;
	int size_vect = 0; //Nombre de proténies présentes dans le vecteur
	
	int count = 0;
	
    for(int k = 0; k < pin.getNbSequences();k++)
    //for(int k = 2958; k < 2961  ;k++)
    //2958:6525, 2959:5957
    {	
		int globalmax_i = 0;
		int globalmax_j = 0;
		int offsetEnd = __bswap_32(pin.getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin.getSequenceOffsetTable()[k]);
		

	
		vector<vector<int>> M((offsetEnd - offsetBegin +1), vector<int> (sizeref+1));
		//vector<vector<int>> MEMO((offsetEnd - offsetBegin +1), vector<int> (sizeref+1));
		
		//int M[offsetEnd - offsetBegin +1][sizeref+1];
		//int MEMO[offsetEnd - offsetBegin +1][sizeref+1];
		
		//int **M = new int*[offsetEnd-offsetBegin+1];
		//for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			//M[i] = new int[sizeref+1];
		//}
		//int **MEMO = new int*[offsetEnd-offsetBegin+1];
		//for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			//MEMO[i] = new int[sizeref+1];
		//}
		
		for(int i = 0; i < offsetEnd - offsetBegin +1;i++)
		{
			M[i][0] = 0;
			//MEMO[i][0] = 0;
		}
		for(int j = 0; j < sizeref +1;j++)
		{
			M[0][j] = 0;
			//MEMO[0][j] = 0;
		}
		
		int max_colonne[sizeref] = {0}; //Attention on commence bien à 0 ici pour la premiere colonne de la matrice.
		
		for(int i = 1; i < offsetEnd-offsetBegin +1; i++)
		{
			int max_ligne = 0;
			for (int j = 1; j < sizeref+1; j++)
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
				
				max_colonne[j-1] = max_colonne[j-1] - ext_pen;
				
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
				
				max_ligne = max_ligne - ext_pen;


				
				int value;
				
				if(M[i-1][j-1] + blosum[(int)table[offsetBegin+i]][AAValue[j-1]] < 0 && a < 0 && b < 0) //Check si il faut pas mettre offsetBegin+i-1
				{
					value = 0;
					//MEMO[i][j] = 0;
				}
				
				else if (a < M[i-1][j-1] + blosum[(int)table[offsetBegin+i]][AAValue[j-1]] && b < M[i-1][j-1] + blosum[(int)table[offsetBegin+i]][AAValue[j-1]])
				{
					value = M[i-1][j-1] + blosum[(int)table[offsetBegin+i]][AAValue[j-1]];
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
				
				M[i][j] = value;
				
				if(M[globalmax_i][globalmax_j] < value)
				{
					globalmax_i = i;
					globalmax_j = j;
				}
			}
		}
		/*for(int i = 1; i < offsetEnd-offsetBegin +1; i++)
		{
			for (int j = 1; j < sizeref+1; j++)
			{
				cout << i << endl;
				cout << j << endl;
				cout << MEMO[i][j] << endl;
				cout << "ok" << endl;
			}
		}*/
		
		int score = M[globalmax_i][globalmax_j];
		//cout << "Score : " << score << endl;
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
		//for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			//delete [] M[i];
		//}
		//delete [] M;
		//for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			//delete [] MEMO[i];
		//}
		//delete [] MEMO;
	}
	/*for(int i = 0; i < 10; i++)
	{
		cout << protVect[i]->getScore() << endl;
		cout << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[protVect[i]->getNb()])) << endl;
	}*/
}


