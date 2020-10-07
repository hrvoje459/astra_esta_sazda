
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// KRIPTIRANJE

void round(unsigned char** cypherText, unsigned char** plainText, unsigned char** prosireniKljuc, int i) {
    byteSub(cypherText);
    rowShift(cypherText);
    columnMix(cypherText);
    RoundKeyAdd(cypherText, prosireniKljuc, i);
}
void finalRound(unsigned char** cypherText, unsigned char** prosireniKljuc, int i) {
    byteSub(cypherText);
    rowShift(cypherText);
    RoundKeyAdd(cypherText, prosireniKljuc, i);
}
void crypt(unsigned char** cypherText, unsigned char** plainText, unsigned char** prosireniKljuc) {
    int i = 0;
    RoundKeyAdd(cypherText, prosireniKljuc, i);
    for (i = 1; i < 10; i++) {
        round(cypherText, plainText, prosireniKljuc, i);
    }
    finalRound(cypherText, prosireniKljuc, i);
}

// DEKRIPTIRANJE
void inverseRound(unsigned char** unCypherText, unsigned char** cypherText, unsigned char** prosireniKljuc, int i) {
    inverseRoundKeyAdd(unCypherText, prosireniKljuc, i);
    inverseColumnMix(unCypherText);
    inverseRowShift(unCypherText);
    inverseByteSub(unCypherText);
}
void inverseFinalRound(unsigned char** unCypherText, unsigned char** prosireniKljuc, int i) {
    inverseRoundKeyAdd(unCypherText, prosireniKljuc, i);
    inverseRowShift(unCypherText);
    inverseByteSub(unCypherText);
}

void deCrypt(unsigned char** unCypherText, unsigned char** cypherText, unsigned char** prosireniKljuc) {
    int i = 10;
    inverseFinalRound(unCypherText, prosireniKljuc, i);
    for (i = 9; i > 0; i--) {
        inverseRound(unCypherText, cypherText, prosireniKljuc, i);
    }
    inverseRoundKeyAdd(unCypherText, prosireniKljuc, i);
}

// MAIN
int main(void) {
    unsigned char** tablicaPlainText;
    unsigned char** tablicaCypherText;
    unsigned char** tablicaUnCypherText;

    unsigned char** kljuc;
    unsigned char** prosireniKljuc;

    tablicaPlainText = new unsigned char*[4];
    tablicaCypherText = new unsigned char*[4];
    tablicaUnCypherText = new unsigned char*[4];
    kljuc = new unsigned char*[4];

    prosireniKljuc = new unsigned char*[44];

    for (int i = 0; i < 4; i++) {
        tablicaPlainText[i] = new unsigned char[4];
        tablicaCypherText[i] = new unsigned char[4];
        tablicaUnCypherText[i] = new unsigned char[4];
        kljuc[i] = new unsigned char[4];
    }

    for (int i = 0; i < 44; i++) {
        prosireniKljuc[i] = new unsigned char[4];
    }
    tablicaPlainText[0][0] = 0x32;
    tablicaPlainText[1][0] = 0x43;
    tablicaPlainText[2][0] = 0xf6;
    tablicaPlainText[3][0] = 0xa8;

    tablicaPlainText[0][1] = 0x88;
    tablicaPlainText[1][1] = 0x5a;
    tablicaPlainText[2][1] = 0x30;
    tablicaPlainText[3][1] = 0x8d;

    tablicaPlainText[0][2] = 0x31;
    tablicaPlainText[1][2] = 0x31;
    tablicaPlainText[2][2] = 0x98;
    tablicaPlainText[3][2] = 0xa2;

    tablicaPlainText[0][3] = 0xe0;
    tablicaPlainText[1][3] = 0x37;
    tablicaPlainText[2][3] = 0x07;
    tablicaPlainText[3][3] = 0x34;

    tablicaCypherText[0][0] = 0x32;
    tablicaCypherText[1][0] = 0x43;
    tablicaCypherText[2][0] = 0xf6;
    tablicaCypherText[3][0] = 0xa8;

    tablicaCypherText[0][1] = 0x88;
    tablicaCypherText[1][1] = 0x5a;
    tablicaCypherText[2][1] = 0x30;
    tablicaCypherText[3][1] = 0x8d;

    tablicaCypherText[0][2] = 0x31;
    tablicaCypherText[1][2] = 0x31;
    tablicaCypherText[2][2] = 0x98;
    tablicaCypherText[3][2] = 0xa2;

    tablicaCypherText[0][3] = 0xe0;
    tablicaCypherText[1][3] = 0x37;
    tablicaCypherText[2][3] = 0x07;
    tablicaCypherText[3][3] = 0x34;

    kljuc[0][0] = 0x2b;
    kljuc[1][0] = 0x7e;
    kljuc[2][0] = 0x15;
    kljuc[3][0] = 0x16;

    kljuc[0][1] = 0x28;
    kljuc[1][1] = 0xae;
    kljuc[2][1] = 0xd2;
    kljuc[3][1] = 0xa6;

    kljuc[0][2] = 0xab;
    kljuc[1][2] = 0xf7;
    kljuc[2][2] = 0x15;
    kljuc[3][2] = 0x88;

    kljuc[0][3] = 0x09;
    kljuc[1][3] = 0xcf;
    kljuc[2][3] = 0x4f;
    kljuc[3][3] = 0x3c;

    keySchedule(kljuc, prosireniKljuc);

    crypt(tablicaCypherText, tablicaPlainText, prosireniKljuc);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tablicaUnCypherText[i][j] = tablicaCypherText[i][j];
        }
    }
    deCrypt(tablicaUnCypherText, tablicaCypherText, prosireniKljuc);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << (int)(tablicaPlainText[j][i]) << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << (int)(tablicaCypherText[j][i]) << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << hex << (int)(tablicaUnCypherText[j][i]) << " ";
        }
    }
    return 0;
}
