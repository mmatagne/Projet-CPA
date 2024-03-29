/* La classe Input possède les informations relatives au fichier .pin de la database. */

#include "input.h"


using namespace std;

Input::Input(string pinfile) {
	filename = pinfile;
}
Input::Input(){}

Input::~Input(){
	
}


//Lit le fichier binaire .pin et stocke les valeurs lues dans les attributs
//correspondants.
//bswap_32 est utilisé pour transformer les nombres de big endian a little endian.
void Input::readfile() {					 
	ifstream file (filename, ios::in | ios::binary); //Fichier ouvert en tant que fichier binaire
	if(!file.is_open()) {
		cout << "Problème à la lecture du fichier base de données : " << filename << endl;
		exit(EXIT_FAILURE);
	}
	file.read( (char*)(&version), sizeof(version) );
	version = __bswap_32(version);
	file.read( (char*)(&db_type), sizeof(db_type) );
	db_type = __bswap_32(db_type);
	file.read( (char*)(&title_length), sizeof(title_length) ); 
	title_length = __bswap_32(title_length);
	title = new char[title_length]; 					
	file.read(title, title_length);
	file.read( (char*)(&timestamp_length), sizeof(timestamp_length) );
	timestamp_length = __bswap_32(timestamp_length);
	timestamp = new char[timestamp_length];
	file.read(timestamp, timestamp_length );
	file.read( (char*)(&nbSequences), sizeof(nbSequences) );
	nbSequences = __bswap_32(nbSequences);
	file.read( (char*)(&residueCount), sizeof(residueCount) );
	file.read( (char*)(&maxSequence), sizeof(maxSequence) );
	maxSequence = __bswap_32(maxSequence);
	headerOffsetTable = new int[nbSequences+1]; 
	sequenceOffsetTable = new int[nbSequences+1];
	file.read( (char*)(headerOffsetTable), sizeof(int)*(nbSequences+1) );
	file.read( (char*)(sequenceOffsetTable), sizeof(int)*(nbSequences+1) );
	file.close();
}


//Plusieurs accesseurs sont prévus pour les attributs de la classe Input 

int* Input::getHeaderOffsetTable() {		 
	return headerOffsetTable;
}

int* Input::getSequenceOffsetTable() {
	return sequenceOffsetTable;
}

int Input::getNbSequences() {
	return nbSequences;
}

int Input::getNbRes() {
	return residueCount;
}

int Input::getMaxSequence() {
	return maxSequence;
}

char* Input::getTitle() {
	return title;
}

char* Input::getTime() {
	return timestamp;
}
