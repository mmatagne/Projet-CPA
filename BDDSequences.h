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
	
	public:
	BDDSequences(string db_psqfile, int db_size);
	~BDDSequences();
	map<char,int> conversion;
	char* getTable();
	
	
};
