#ifndef PROTEINE_H
#define PROTEINE_H
#include <string>
#include <vector>
using std::vector;
using std::string;

class Proteine
{
	private:
	string name;
	vector<int> data;
	
	
	public:
	Proteine(string new_name, vector<int> data);
	~Proteine();
	void setName(string new_name);
	void setData(vector<int> new_data);
	string getName() const;
	vector<int> getData() const;
	int getLength() const;
	bool operator==(const Proteine &protDroite) const;
	
	
	
};

	

#endif
