#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using std::vector;
using std::string;
using namespace std;

class Sequence
{
	private:
	string filename;
	ifstream psq;
	//int convert(char a);
	
	public:
	Sequence(string psqfile);
	~Sequence();
	vector<int> getSequence();
	map<char,int> conversion;
	
	
};

