/* L'utilité de la classe BBDSequences est de ramener toutes les séquences d'acides aminés de la database (du fichier .psq) vers la mémoire RAM de sorte à y avoir un accès plus rapide*/

#ifndef BDD_H
#define BDD_H
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using std::vector;
using std::string;
using namespace std;

class BDDSequences
{
	private:
	char* table;
	string filename;
	const static map<char,int> conversion;
	
	public:
	BDDSequences(string db_psqfile, int db_size);
	BDDSequences();
	~BDDSequences();
	const static map<char,int>& getConversionMap(); 
	char* getTable();
	
	
};
#endif
