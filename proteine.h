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
	//static map<char,int> conversion;

	
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
