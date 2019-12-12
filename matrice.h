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
	//int** matrice;
	int matrice[28][28];
	Matrice(string file);
	~Matrice();
	//int* getMatrice();
};

