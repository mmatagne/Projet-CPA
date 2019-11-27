all : input.o sequence.o proteine.o header.o BDDSequences.o main2711.cpp
	g++ -o out input.o sequence.o BDDSequences.o proteine.o header.o main2711.cpp 
input.o: input.cpp
	g++ -c input.cpp
sequence.o: sequence.cpp
	g++ -c sequence.cpp
BDDSequences.o: BDDSequences.cpp
	g++ -c BDDSequences.cpp
proteine.o: input.cpp
	g++ -c proteine.cpp
header.o: header.cpp
	g++ -c header.cpp
clean:
	rm *.o
