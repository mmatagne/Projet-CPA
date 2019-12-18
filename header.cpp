/* La classe Header permet de traiter les fichiers binaires .phr contenant 
 * le titre ainsi que le BL_ORD_ID des différentes protéines */

#include <iostream>
#include <fstream> 
#include "header.h"

using namespace std;

Header::Header(string phrfile) {
	filename = phrfile;
	phr.open(filename, ios::in | ios::binary);
	if(!phr.is_open()) {
		cout << "Problème à la lecture du fichier base de données : " << phrfile << endl;
		exit(EXIT_FAILURE);
	}
}

Header::~Header(){
	phr.close();
}


//getTitle prend en argument l'offset d'une protéine de la database et récupère son titre
char* Header::getTitle(int offset) { 
	phr.seekg(offset);
	uint8_t var;
	while(phr.read( (char*)(&var), sizeof(var)))
	{
		if(var == 160) //correspond à A0 en hexadécimal
		{
			phr.read( (char*)(&var), sizeof(var));
			if(var == 128) //correspond à 80 en hexadécimal
			{
				phr.read( (char*)(&var), sizeof(var));
				if(var == 26) //correspond à 1A en hexadécimal
				{
					phr.read( (char*)(&var), sizeof(var));//ce qui suit A0801A correspond à la taille sur laquelle est codé le titre
					
					if(var >= 128) //si le premeir bit est à 1 : var(-128 met le premier bit à 0) = nombre de bytes sur lequel est codé le nom
					{
						int nbBytes = var-128;
						unsigned long title_length ;
						uint8_t x;
						title_length = 0;
						for (int j = 0; j < nbBytes; j++){ 
							phr.read((char*)&x, 1);
							title_length = title_length << 8 | x; //left shift de 8 cases et OR p/r à la variable x venant d'etre lue
						}
						
						title = new char[title_length+1];
						title[title_length] = '\0';
						phr.read(title, title_length*sizeof(char));
						return title;
					}
					else // si le premier bit est à 0 : var = longueur du titre
					{
						title = new char[var+1];
						title[var] = '\0';
						phr.read(title, var*sizeof(char));
						return title;
					}
				}
			}
		}
	}
}


//getID prend en argument l'offset d'une protéine de la database et récupère son ID
int Header::getID(int offset) {  
	phr.seekg(offset);
	uint8_t var;
	while(phr.read( (char*)(&var), sizeof(var)))
	{
		if(var == 2)    //lorsqu'on tombe sur un 02 en hexadécimal (correspond également à 2 en base 10), on sait que le bit 
		{				//qui suit correspond aux nombres de bits sur lesquels est codé l'ID	
			phr.read( (char*)(&var), sizeof(var));
         	        unsigned long ID;
			uint8_t x;
			ID = 0;
			for (int j = 0; j < var; j++){ 
				phr.read((char*)&x, 1);
				ID = ID << 8 | (unsigned long)x;
			}
			return ID;
		}
	}
	return 0;
}







