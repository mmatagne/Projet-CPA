#ifndef PROTEINE_H
#define PROTEINE_H
#include <string>
#include <vector>
#include <forward_list>

using namespace std;

class Proteine
{
	private:
	int protNb;
	forward_list<int> listeInconnue;
	forward_list<int> listeDb;
	
	public:
	Proteine(int new_protNb, forward_list<int> new_listeInconnue, forward_list<int> new_listeDb);
	~Proteine();
	int getNb() const;
	void printResult();
};

	

#endif
