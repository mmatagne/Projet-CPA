all : input.o matrice.o proteine.o header.o BDDSequences.o algorithme.o projet.cpp
	g++ -Ofast -o projet input.o matrice.o BDDSequences.o proteine.o header.o algorithme.o projet.cpp 
input.o: input.cpp
	g++ -c input.cpp
matrice.o: matrice.cpp
	g++ -c matrice.cpp
BDDSequences.o: BDDSequences.cpp
	g++ -c BDDSequences.cpp
proteine.o: proteine.cpp
	g++ -c proteine.cpp
header.o: header.cpp
	g++ -c header.cpp
algorithme.o: algorithme.cpp
	g++ -Ofast -c algorithme.cpp
clean:
	rm *.o
