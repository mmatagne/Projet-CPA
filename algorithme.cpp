/*La classe Algorithme possède tout le code relatif à l'exécution de 
 * l'algorithme de Smith-Waterman ainsi qu'à l'exécution du traceback 
 * La pricipale optimisation apportée est le fait d'utiliser uniquement
 * un tableau à une dimension représentant une ligne de la matrice de
 * scores au lieu d'un tableau 2D.
 * La mémoisation est utilisée dans le stockage de maximums par ligne et 
 * par colonne.*/

#include <iostream>
#include "algorithme.h"
using namespace std;

Algorithme::Algorithme(Input* input, BDDSequences* bddsequences, vector<int>* query_prot, int** mat, int o_p, int ext_p)
{
	pin = input;
	sequences = bddsequences;
	open_pen = o_p;
	ext_pen = ext_p;
	sizeref = (*query_prot).size();
	blosum = mat;
	AAValue = query_prot->data();
	
	scoresvect = new int[pin->getNbSequences()];
	
}

Algorithme::~Algorithme(){
	
	delete [] scoresvect;
}

int Algorithme::getMax(int* array , int array_size){
	int index_of_max = 0;
	for(int i=0; i<array_size; i++){
		if(array[i]>array[index_of_max]) {
			index_of_max = i;
		}
	}
	return index_of_max;
}

int* Algorithme::getScoresTable(){
	return scoresvect;
}
	
void Algorithme::run(){
	
	char* table = sequences->getTable();
	
	int nbseq = pin->getNbSequences();
	int a;
	int b;
	/*
	On calcule ci-dessous les scores pour chacune des protéines de la database.
	On commence une boucle for sur toutes les protéines présentes dans la database.*/	
    for(int k = 0; k < nbseq;k++)
    {	
		
		int sauve = 0;
		int maximum = 0; //correspondra au maximum en temps réel lors du calcul des scores
		int offsetEnd = __bswap_32(pin->getSequenceOffsetTable()[k+1]); //donne l'indice de la (k+1)ème protéine, correspond donc au premier élément ne concernant pas la séquence de la k ème protéine qui nous intéresse
		int offsetBegin = __bswap_32(pin->getSequenceOffsetTable()[k]); //donne l'indice de la k ème protéine
		
		int T[sizeref+1] = {}; //à la place d'utiliser une matrice pour calculer les scores, on utilise un tableau de la taille d'une ligne afin d'économiser de la mémoire.
		
		int max_colonne[sizeref] = {0};  //on crée un vecteur contenant le maximum pour chacune des colonnes
		
		for(int i = 1; i < offsetEnd-offsetBegin; i++) //on commence un for sur le nombre d'éléments de la séquence k (taille de la protéine)
		{
			int max_ligne = 0; //correspond à la valeur maximale obtenue par un gap_extension sur la ligne considérée.
			for (int j = 1; j < sizeref+1;j++) //on commence un for sur la taille de la protéine inconnue
			{
				
				/*On commence par mettre les max de la colonne ainsi que de la ligne à jour. Pour ce faire, on vérifie s'il est plus avantageux de partir 
				* de l'élément juste en haut ou juste à gauche dans la matrice ou plutôt depuis l'élément qui a été le plus avantageux jusqu'ici.
				*/		
				if(T[j]-open_pen < max_colonne[j-1]-ext_pen)
				{
					
					a = max_colonne[j-1]-ext_pen;
				}
				
				else
				{
					a = T[j]-open_pen;
					max_colonne[j-1] = a;
				}
				
				max_colonne[j-1] = max_colonne[j-1] - ext_pen;
				
				
				if(T[j-1]-open_pen < max_ligne-ext_pen)
				{
					b = max_ligne-ext_pen;
				}
				
				else
				{
					b = T[j-1]-open_pen;
					max_ligne = b;
				}
				
				max_ligne = max_ligne - ext_pen;

				/* On applique ici l'algorithme de Smith-Waterman en comparant les 4 scores possibles pour un élément.
				*  A savoir les scores calculés à partir de l'élément en haut à gauche, en haut, à gauche et le score nul.
				*/			
				int value;
				
				if(sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] < 0 && a < 0 && b < 0) //cas où zéro est le meilleur score
				{
					value = 0;
					
				}
				
				else if (a < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] && b < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]]) //cas où le score calculé en diagonal est le meilleur
				{
					value = sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]];
				}
				
				else if (a < b)//cas où le score calculé depuis la même ligne est le meilleur
				{
					value = b;
				}
				else //cas où le score calculé depuis la même colonne est le meilleur
				{
					value = a;
				}
				
				sauve = T[j]; //on sauvegarde l'élément qu'on va remplacer car il sera nécessaire pour la prochaine itération
				T[j] = value; //on remplace l'élément par la valeur qu'on vient de trouver
				
				if(maximum < value)
				{
					maximum = value; //on stocke la valeur trouvée si celle-ci est plus grande que le maximum du moment
				}
			}
		}
		scoresvect[k] = maximum; //on stock le maximum correspondant au score de la protéine dans un vecteur qui contiendra les scores de toutes les protéines de la database	
	}
}


//getAlignement effectue l'opération de traceback, et renvoie un vecteur 
// contenant les 10 meilleures protéines.
Proteine** Algorithme::getAlignment(int nb_prot)
{
	//DEBUT DU TRACEBACK 
	
	//création vecteur de Proteines.
	protVect = new Proteine*[nb_prot];
	int k = 0;
	int a;
	int b;
	char* table = sequences->getTable();
	int nbseq = pin->getNbSequences();
	
	for(int iota=0;iota<nb_prot;iota++){ //on va chercher les 10 meilleurs scores dans le vecteur contenant ceux-ci
		k = getMax(scoresvect, nbseq);
		scoresvect[k]=-1; //on supprime le meilleur élément trouvé dans le vecteur pour qu'à la prochaine itération, on trouve le meilleur score suivant
		
		// CONSTRUCTION DE MEMO SUR BASE DE L'ALGO
		/*Pour ces 10 protéines ayant les meilleurs scores, on recommence l'opération du calcul des scores mais 
		 * cette fois en créant parallèlement une matrice MEMO qui nous indiquera comment chaque élément de la 
		 * matrice des scores à été trouvé. Il y a 4 possibilités explicitées plus bas lors du traceback. 
		 * On sauvegarde également les index du maximum global de cette matrice des scores.
		*/
		int sauve = 0;
		int globalmax_i = 0;
		int globalmax_j = 0;
		int maximum = 0;
		int offsetEnd = __bswap_32(pin->getSequenceOffsetTable()[k+1]);
		int offsetBegin = __bswap_32(pin->getSequenceOffsetTable()[k]);
		
		int T[sizeref+1] = {};
		
		int max_colonne[sizeref] = {0}; 
		
		int **MEMO = new int*[offsetEnd-offsetBegin+1];
		for(int i = 0; i < offsetEnd-offsetBegin+1; ++i) {
			MEMO[i] = new int[sizeref+1];
		}
		
		for(int i = 0; i < offsetEnd-offsetBegin+1; ++i)
		{
			MEMO[i][0] = 0;
		}
		
		for(int j = 0; j < sizeref+1; ++j)
		{
			MEMO[0][j] = 0;
		}
		
		for(int i = 1; i < offsetEnd-offsetBegin; i++)
		{
			int max_ligne = 0;
			for (int j = 1; j < sizeref+1;j++)
			{
				
					
				if(T[j]-open_pen < max_colonne[j-1]-ext_pen)
				{
					a = max_colonne[j-1]-ext_pen;
				}
				
				else
				{
					a = T[j]-open_pen;
					max_colonne[j-1] = a;
				}
				
				max_colonne[j-1] = max_colonne[j-1] - ext_pen;
				
				if(T[j-1]-open_pen < max_ligne-ext_pen)
				{
					b = max_ligne-ext_pen;
				}
				
				else
				{
					b = T[j-1]-open_pen;
					max_ligne = b;
				}
				
				max_ligne = max_ligne - ext_pen;
				
				int value;
				
				if(sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] < 0 && a < 0 && b < 0)
				{
					value = 0;
					MEMO[i][j] = 0;
				}
				
				else if (a < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]] && b < sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]])
				{
					value = sauve + blosum[(int)table[offsetBegin+i-1]][AAValue[j-1]];
					MEMO[i][j] = 1;
				}
				
				else if (a < b)
				{
					value = b;
					MEMO[i][j] = 2;
				}
				else
				{
					value = a;
					MEMO[i][j] = 3;
				}
				sauve = T[j];
				T[j] = value;
				
				if(maximum < value)
				{
					maximum = value;
					globalmax_i = i;
					globalmax_j = j;
				}
			}
		}
		
		//DEBUT DU TRACEBACK DANS LA MATRICE MEMO	
		int i = globalmax_i;
		int j = globalmax_j;
		forward_list<int> listeInconnue;
		forward_list<int> listeDb;

		while(MEMO[i][j] != 0)  //on arrête le traceback lorsqu'on tombe sur un élément nulle dans la MEMO
		{
			/*
			Si on tombe sur un 1 dans la MEMO, cela signifie que le score a été calculé depuis l'élément diagonale en haut à gauche 
			* dans la matrice des scores. On ajoute donc cet élément aux deux séquences correspondant à la protéine inconnue ainsi 
			* qu'à celle de la database qu'on va garder. On fixe ensuite i et j correspondant à ce nouvel élément et, à condition 
			* que celui-ci soit différent de zéro, on retourne dans la boucle pour vérifier comment celui-ci a été calculé. Les éléments 
			* sont par ailleurs rajoutés au début des listes de sorte à ce que les séquences se retrouvent dans l'ordre à la fin de l'opération.
			*/
			if(MEMO[i][j] == 1)
			{
				listeInconnue.push_front(AAValue[j-1]);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
				j -= 1;
			}
			/*
			* Le 3 signifie que le score a été calculé depuis l'élément de gauche dans la matrice des scores. Cela correspond à un 'gap' 
			* dans la séquence de la protéine inconnue, on lui ajoute donc un zéro correspondant au caractère '-'. Pour la protéine de 
			* la database, l'élément correspondant est ajouté. On ne change donc que de colonne et que l'index i est affecté d'un -1.
			*/
			if(MEMO[i][j] == 3)
			{
				listeInconnue.push_front(0);
				listeDb.push_front(table[offsetBegin+i-1]);
				i -= 1;
			}
			/*
			Le 2 signifie que le score a été calculé depuis l'élément en haut dans la matrice des scores. Il s'agit donc de l'opération
			* duale au cas précédent.
			*/
			if(MEMO[i][j] == 2)
			{
				listeInconnue.push_front(AAValue[j-1]);
				listeDb.push_front(0);
				j -= 1;
			}
		}

		for(int i = 0; i < offsetEnd-offsetBegin; ++i) {
			delete [] MEMO[i];
		}
		delete [] MEMO; //à la fin du traceback, on supprime la MEMO de sorte à libérer l'espace mémoire qui lui était alloué
		protVect[iota] = new Proteine(k,maximum,listeInconnue,listeDb); //on rajoute la protéine étudiée au vecteur à renvoyer
	}
	return protVect;
}

