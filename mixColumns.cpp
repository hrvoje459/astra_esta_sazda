
#include "aesHeader.h"
#include <fstream>
#include <iostream>

using namespace std;

unsigned char mullTable[4][4] = {
    {0x2, 0x3, 0x1, 0x1}, {0x1, 0x2, 0x3, 0x1}, {0x1, 0x1, 0x2, 0x3}, {0x3, 0x1, 0x1, 0x2}};
unsigned char inverseMullTable[4][4] = {{14, 11, 13, 9}, {9, 14, 11, 13}, {13, 9, 14, 11}, {11, 13, 9, 14}};

// IZMJESAJ STUPCE
void columnMix(unsigned char** cypherText) {
    unsigned char helperArray[4];
    for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
            helperArray[l] = cypherText[l][k];
        }
        for (int i = 0; i < 4; i++) {
            unsigned char temp = 0;
            for (int j = 0; j < 4; j++) {
                temp ^= gPoljePomnozi(mullTable[i][j], helperArray[j]);
            }
            cypherText[i][k] = temp;
        }
    }
}

void inverseColumnMix(unsigned char** unCypherText) {
    unsigned char helperArray[4];
    for (int k = 0; k < 4; k++) {
        for (int l = 0; l < 4; l++) {
            helperArray[l] = unCypherText[l][k];
        }
        for (int i = 0; i < 4; i++) {
            unsigned char temp = 0;
            for (int j = 0; j < 4; j++) {
                temp ^= gPoljePomnozi(inverseMullTable[i][j], helperArray[j]);
            }
            unCypherText[i][k] = temp;
        }
    }
}