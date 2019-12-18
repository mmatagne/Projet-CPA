#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <string.h>
#include <time.h>
#include <vector>
#include <map>
#include <forward_list>
#include "header.h"
#include "algorithme.h"


using namespace std;


int main(int argc, char **argv) {
	
	if(argc < 3)
	{
		cout << "Erreur dans le nombre de paramètres." << endl;
		cout << "Veuillez introduire le nom du fichier de la protéine puis celui de la base de données." << endl;
		cout << "Les paramètres optionnels sont : la matrice BLOSUM précédée du flag -m" << endl;
		cout << "-la matrice BLOSUM précédée du flag -m" << endl;
		cout << "-le gap open penalty précédé du flag -gop" << endl;
		cout << "-le gap extension penalty précédé du flag -gep" << endl;
		return EXIT_FAILURE;
	}
	
	clock_t t; //cette variable sert à mesurer le temps d'exécution
	
	//On initialise les paramètres par défaut.
	char matrix_name[] = "BLOSUM62.txt";
	int open_pen = 11;
	int ext_pen = 1;
	
	char* prot_name = argv[1];
	char* db_raw = argv[2];
	
	char namepin[strlen(db_raw)]; 
	char namepsq[strlen(db_raw)]; 
	char namephr[strlen(db_raw)]; 
	
	strcpy(namepin,db_raw);
	strcpy(namepsq,db_raw);
	strcpy(namephr,db_raw);
	
	strcat(namepin,".pin");
	strcat(namepsq,".psq");
	strcat(namephr,".phr");

	
	for(int i = 3; i < argc; i++)
	{
		if(!strcmp(argv[i],"-m"))
		{
			strcpy(matrix_name,argv[i+1]);
		}
		if(!strcmp(argv[i],"-gop"))
		{
			open_pen = atoi(argv[i+1]);
		}
		if(!strcmp(argv[i],"-gep"))
		{
			ext_pen = atoi(argv[i+1]);
		}
	}

	//Initialisation des différents objets.
	Input pin(namepin); 	//on créé un objet de la classe Input prenant comme attribut le fichier .pin
	pin.readfile();	//la fonction readfile permet de donner les valeurs aux attributs de l'objet
	
	int sizedb =  __bswap_32(pin.getSequenceOffsetTable()[pin.getNbSequences()]);
	BDDSequences sequences(namepsq, sizedb);
	map<char,int> conversion = BDDSequences::getConversionMap(); //renvoie la map définie dans BBDSequences qui fait correspondre chaque caractère d'acide aminé à un entier, défini par le formalisme blast
	Matrice matscore(matrix_name);
	
	// Lecture de la proteine query
	vector<int> AAValue_vector;
	ifstream protFile (prot_name);
	
	if (!protFile) 
	{
		cout << "Erreur à l'ouverture du fichier de la query." << endl;
	}
	
	//Lecture de la première ligne du fichier de la query (contient le titre de la protéine).
	string firstLine;
	getline(protFile,firstLine);
	
	char ch;
	while(protFile >> noskipws >> ch) 
	{
		if(ch != '\n') 
		{
			//On stocke toutes les valeurs de int correspondant aux char dans un vecteur AAValue
			AAValue_vector.push_back(conversion[ch]); 
		}
	}
	protFile.close(); // Fin de la lecture de la proteine query
	
	
	
	//Lancement de l'algorithme de Smith-Waterman.
	Algorithme algorithme(&pin, &sequences, &AAValue_vector, matscore.getMatrice(), open_pen, ext_pen);
	algorithme.run();
	
	//Lancement du traceback pour les 10 meilleures protéines (paramètre variable),
	//et récupération d'un vecteur contentant les 10 meilleures protéines.
	Proteine** protVect = algorithme.getAlignment(10);
	
	t = clock() - t; //Marque la fin du temps d'exécution du programme.
	
	Header phr(namephr);
	
	
	//Affichage des résultats de manière identique à swipe.
	
	cout << "Database title : " << pin.getTitle() << endl;
	cout << "Database time : " << pin.getTime() << endl;
	cout << "Database size : " << pin.getNbRes() << " residues in " << pin.getNbSequences() << " sequences" << endl;
	cout << "Longest db seq : " << pin.getMaxSequence() << endl;
	cout << "Query file name : " << prot_name << endl;
	cout << "Query length : " << AAValue_vector.size() << " residues" << endl;
	cout << "Query description : " << firstLine << endl;
	cout << "Score matrix : " << matrix_name << endl;
	cout << "Gap penalty : " << open_pen << "+" << ext_pen << "k" << endl;
	cout << "Alignements shown : " << "10" << endl;
	cout << "Symbol type : " << "Amino acid" << endl;
	cout << endl;
	cout << endl;
	
	cout << "Elapsed : " << ((float)t)/CLOCKS_PER_SEC << "s" << endl;
	
	cout << endl;
	cout << endl;
	
	
	cout << "Sequences producing significant alignements:" << endl;
	cout << endl;
	
	for(int i = 0; i < 10; i++)
	{
		cout << left << setw(140) << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[protVect[i]->getNb()])) << fixed << protVect[i]->getScore() << endl;
	}
	
	cout << endl;
	cout << endl;
	for(int i = 0; i < 10; i++)
	{
		cout << "<" << "gnl|BL_ORD_ID|" << phr.getID(__bswap_32(pin.getHeaderOffsetTable()[protVect[i]->getNb()])) << " " << phr.getTitle(__bswap_32(pin.getHeaderOffsetTable()[protVect[i]->getNb()])) << endl;
		cout << "Length = " << __bswap_32(pin.getSequenceOffsetTable()[protVect[i]->getNb()+1]) - __bswap_32(pin.getSequenceOffsetTable()[protVect[i]->getNb()]) << endl;
		cout << "Score = " << protVect[i]->getScore() << " bits (" << protVect[i]->getRawScore() << ")" << endl;
		cout << endl;
		protVect[i]->printResult();
		
		cout << endl;
		cout << endl;

	}
	
	//Liberation mémoire vecteur des proteines du traceback :
	for(int i =0; i<10; i++)
	{
		delete protVect[i];
	}
	delete [] protVect;
	
	return 0;
}


