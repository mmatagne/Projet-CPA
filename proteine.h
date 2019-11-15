#ifndef PROTEINE_H
#define PROTEINE_H
#include <string>
#include <vector>
using std::vector<int>;
using std::string;

class Proteine
{
	private:
	vector<int> data;
	string name;
	
	public:
	Proteine();
	~Proteine();
	void setName(string new_name);
	void setData(vector<int> new_data);
	string getName() const;
	vector<int> getData() const;
	int getLength() const;
	
	
	
};
	

#endif
