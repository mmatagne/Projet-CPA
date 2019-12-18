/* La classe protéine possède des attributs relative à une protéine de la database tel que son offset dans la database, son score relatif
à une protéine inconnue traitée dans le main ainsi que les séquences d'acides aminés des deux protéines correspondant au score calculé.  */

#ifndef PROTEINE_H
#define PROTEINE_H
#include <string>
#include <vector>
#include <map>
#include <forward_list>

using namespace std;

class Proteine
{
	private:
	int protNb;
	int score;
	forward_list<int> listeInconnue;
	forward_list<int> listeDb;

	
	public:
	Proteine(int new_score, int new_protNb, forward_list<int> new_listeInconnue, forward_list<int> new_listeDb);
	Proteine();
	~Proteine();
	int getNb() const;
	int getScore() const;
	int getRawScore() const;
	void printResult();
};

	

#endif
