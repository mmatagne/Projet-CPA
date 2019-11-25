#include "input.h"


using namespace std;

Input::Input(string pinfile) {
	filename = pinfile;
}

Input::~Input(){
	
}

void Input::readfile() {
	ifstream file (filename, ios::in | ios::binary);
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
}


int* Input::getHeaderOffsetTable() {
	return headerOffsetTable;
}

int Input::getNbSequences() {
	return nbSequences;
}

