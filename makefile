all : input.o matrice.o proteine.o header.o BDDSequences.o algorithme.o mainliste2.cpp
	g++ -Ofast -o out input.o matrice.o BDDSequences.o proteine.o header.o algorithme.o mainliste2.cpp 
input.o: input.cpp
	g++ -c input.cpp
matrice.o: matrice.cpp
	g++ -c matrice.cpp
BDDSequences.o: BDDSequences.cpp
	g++ -c BDDSequences.cpp
proteine.o: input.cpp
	g++ -c proteine.cpp
header.o: header.cpp
	g++ -c header.cpp
algorithme.o: algorithme.cpp
	g++ -c algorithme.cpp
clean:
	rm *.o
