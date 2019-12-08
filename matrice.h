#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Matrice {
	private:
	string filename;
	void create_matrice();
	
	public:
	int matrice[20][20];
	Matrice(string file);
	~Matrice();
	//int* getMatrice();
};

