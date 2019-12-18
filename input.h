#ifndef INPUT_H
#define INPUT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Input
{
	private:
	string filename;
	int version;
	int db_type;				//correspond au type de base de données (Acide Aminés)
	int title_length;			//correspond à la taille du titre
	char* title;				//correspond au titre
	int timestamp_length;
	char* timestamp;			//correspond à la date de création de la database
	int nbSequences;			//correspond au nombre de protéines dans la database
	int64_t residueCount;		//donne le nombre total d'acides aminés repris dans la database
	int maxSequence;			//donne la longueur de la séquence la plus longue de la database
	int* headerOffsetTable; 	//donne l'offset de la protéine dans le fichier .phr
	int* sequenceOffsetTable;	//donne l'offset de la protéine dans le fichier .psq
	
	public:
	Input(string pinfile);
	Input();
	~Input();
	void readfile();
	int* getHeaderOffsetTable();
	int* getSequenceOffsetTable();
	int getNbSequences();
	int getNbRes();
	int getMaxSequence();
	char* getTitle();
	char* getTime();
};
#endif
