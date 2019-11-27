all : input.o bddsequences.o sequence.o proteine.o header.o mainpropre.cpp
	g++ -o out input.o sequence.o bddsequences.o proteine.o header.o mainpropre.cpp 
input.o: input.cpp
	g++ -c input.cpp
sequence.o: sequence.cpp
	g++ -c sequence.cpp
bddsequences.o: bddsequences.cpp
	g++ -c bddsequences.cpp
proteine.o: input.cpp
	g++ -c proteine.cpp
header.o: header.cpp
	g++ -c header.cpp
clean:
	rm *.o
