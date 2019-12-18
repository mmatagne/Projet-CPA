/*La classe algorithme possède tout le code relatif à l'exécution de l'algorithme de Smith-Waterman. */

#ifndef ALGORITHME_H
#define ALGORITHME_H
#include <iostream>
#include <vector>
#include "input.h"
#include "BDDSequences.h"
#include "matrice.h"
#include "proteine.h"
#include <string>

class Algorithme
{
	private:
	Input* pin;
	BDDSequences* sequences;
	int** blosum;
	int open_pen;
	int ext_pen;
	int* AAValue; // vecteur de la 'query protein'
	int sizeref; // taille du vecteur de la 'query protein'
	int* scoresvect; // table des scores des protéines de la database
	Proteine** protVect;
	int getMax(int* array, int array_size);
	
	
	public:
	Algorithme(Input* input, BDDSequences* bddsequences, vector<int>* query_prot, int** mat, int o_p, int ext_p);
	~Algorithme();
	void run();
	int* getScoresTable();
	Proteine** getAlignment(int nb_prot);
};
#endif
