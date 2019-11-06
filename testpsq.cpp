#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

int main() {
    int8_t i1; //Les int8_t sont des int codés sur 8 bits, donc 1 byte (sizeof(i1) = 1).
    int8_t i2;
    int8_t i3;
    int8_t i4;
    int8_t i5;
    std::ifstream myFile ("P00533.fasta.psq", std::ios::in | std::ios::binary);
    if (!myFile) {
        std::cout << "Error";
    }
    myFile.read((char*) (&i1), sizeof(i1));
    myFile.read((char*) (&i2), sizeof(i2));
    myFile.read((char*) (&i3), sizeof(i3));
    myFile.read((char*) (&i4), sizeof(i4));
    myFile.read((char*) (&i5), sizeof(i5));
    std::cout << (int) i1 << std::endl; //Si on ne convertit pas les int8_t en int à l'affichage ça donne des résultats bizarres.
    std::cout << (int) i2 << std::endl;
    std::cout << (int) i3 << std::endl;
    std::cout << (int) i4 << std::endl;
    std::cout << (int) i5 << std::endl;
}
