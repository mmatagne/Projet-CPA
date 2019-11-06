#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int8_t i1; //Les int8_t sont des int codés sur 8 bits, donc 1 byte (sizeof(i1) = 1).
    std::ifstream myFile ("P00533.fasta.psq", std::ios::in | std::ios::binary);
    if (!myFile) {
        std::cout << "Error";
    }
    while(myFile.read((char*) (&i1), sizeof(i1))) {
	std::cout << (int) i1 << std::endl; //Convertir le int8_t en int est obligatoire pour l'affichage
    }
}
