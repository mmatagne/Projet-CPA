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
	Input pin;
	BDDSequences sequences;
	int** blosum;
	int open_pen;
	int ext_pen;
	int* AAValue; // query protein vector
	int sizeref; // size of query protein vector
	int* scoresvect; // scores table of proteins from database
	
	int getMax(int* array, int array_size);
	
	
	public:
	Algorithme(const Input& input, const BDDSequences& bddsequences, vector<int>& query_prot, Matrice& matrice, int o_p, int ext_p);
	~Algorithme();
	void run();
	int* getScoresTable();
	Proteine** getAlignment(int nb_prot);
};
