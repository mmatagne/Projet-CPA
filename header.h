#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Header
{	
	private:
	string filename;
	ifstream phr;
	char* title2;
	
	public:
	Header(string phrfile);
	~Header();
	char* getTitle(int offset);

};
