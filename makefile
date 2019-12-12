all : input.o matrice.o proteine.o header.o BDDSequences.o main0712.cpp
	g++ -o out input.o matrice.o BDDSequences.o proteine.o header.o main0712.cpp 
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
clean:
	rm *.o
