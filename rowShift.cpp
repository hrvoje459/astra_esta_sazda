
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// POSMAKNI REDOVE
void posmakni(unsigned char* cypherText) {
    unsigned char temp = cypherText[0];
    cypherText[0] = cypherText[1];
    cypherText[1] = cypherText[2];
    cypherText[2] = cypherText[3];
    cypherText[3] = temp;
}
void rowShift(unsigned char** cypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i; j++) {
            posmakni(cypherText[i]);
        }
    }
}
void inverseRowShift(unsigned char** unCypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            posmakni(unCypherText[i]);
        }
    }
}
