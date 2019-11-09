
#include <iostream>
#include <fstream> 
using namespace std;

int main()
{
	ifstream fichier("P00533.fasta.phr", ios::in | ios::binary);
	if(fichier.is_open())
	{
		for(int i=0;i<100;i++) 
		{
			int8_t version;
			fichier.read( (char*)(&version), sizeof(version));  
			cout << hex << (unsigned int)(unsigned char) version << endl;
		}
	}
	fichier.close();
	return 0;
}


//Premier byte donne 30 et le deuxième donne 80, puis 80, 30, a0, 80,...
//Sur le PDF on voit que si ca commmence par 3080 il s'agit d'un début de SequenceOf.
//Le deuxième 3080 indique qu'on commence une Sequence.
//a080 indique qu'on parle du premier item.
//Ensuite on a un 1a, ce qui indique qu'on a un VisibleString.
//Ensuite on a un 5f, qui devrait correspondre à la longueur du string. En effet, 5f en hex = 95 en décimal.
//Donc on aura un string de longueur 95, c'est logique : si on ouvre P00533.fasta, on remarque justement
//que la première ligne est un string de longueur 95 (sp|P00533|EGFR_HUMAN Epidermal growth factor receptor OS=Homo sapiens OX=9606 GN=EGFR PE=1 SV=2).
//Dans l'autre programme testphr2.cpp on réussit à lire le string.

