#include <iostream>
#include <fstream> 
using namespace std;

int main()
{
	ifstream fichier("P00533.fasta.phr", ios::in | ios::binary);
	if(fichier.is_open())
	{
		int8_t version;
		int8_t version2;
		int8_t version3;
		int8_t version4;
		int8_t version5;
		int8_t version6;
		
		fichier.read( (char*)(&version), sizeof(version)); 
		fichier.read( (char*)(&version2), sizeof(version2)); 
		fichier.read( (char*)(&version3), sizeof(version3)); 
		fichier.read( (char*)(&version4), sizeof(version4)); 
		fichier.read( (char*)(&version5), sizeof(version5)); 
		fichier.read( (char*)(&version5), sizeof(version6)); 
		
		cout << hex << (unsigned int)(unsigned char) version << endl;
		cout << hex << (unsigned int)(unsigned char) version2 << endl;
		cout << hex << (unsigned int)(unsigned char) version3 << endl;
		cout << hex << (unsigned int)(unsigned char) version4 << endl;
		cout << hex << (unsigned int)(unsigned char) version5 << endl;
		cout << hex << (unsigned int)(unsigned char) version6 << endl;
	}
	fichier.close();
	return 0;
}
