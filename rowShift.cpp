#include "aesHeader.h"
#include <fstream>
#include <iostream>
using namespace std;

// POSMAKNI REDOVE
void posmakni(unsigned char** cypherText, int n) {
    {
        unsigned char temp = cypherText[n][0];
        cypherText[n][0] = cypherText[n][1];
        cypherText[n][1] = cypherText[n][2];
        cypherText[n][2] = cypherText[n][3];
        cypherText[n][3] = temp;
    }
}
void rowShift(unsigned char** cypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < i; j++) {
            posmakni(cypherText, i);
        }
    }
}
void inverseRowShift(unsigned char** unCypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            posmakni(unCypherText, i);
        }
    }
}
