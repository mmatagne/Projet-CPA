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
	int db_type;
	int title_length;
	char* title;
	int timestamp_length;
	char* timestamp;
	int nbSequences;
	int64_t residueCount;
	int maxSequence;
	int* headerOffsetTable; 
	int* sequenceOffsetTable;
	
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
