#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Phr
{	
	public:
	string filename;
	
	
	
	Phr(string phrfile);
	~Phr();
	void readfile();


};
