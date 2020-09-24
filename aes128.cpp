
#include "aesHeader.h"
#include <fstream>
#include <iostream>
using namespace std;

// KRIPTIRANJE

void round(unsigned char** cypherText, unsigned char** plainText) {
    byteSub(cypherText);
    rowShift(cypherText);
    columnMix(cypherText);
    RoundKeyAdd(cypherText);
}
void finalRound(unsigned char** cypherText) {
    byteSub(cypherText);
    rowShift(cypherText);
    RoundKeyAdd(cypherText);
}
void crypt(unsigned char** cypherText, unsigned char** plainText) {
    RoundKeyAdd(cypherText);
    for (int i = 0; i < 10; i++) {
        round(cypherText, plainText);
    }
    finalRound(cypherText);
}

// DEKRIPTIRANJE
void inverseRound(unsigned char** unCypherText, unsigned char** cypherText) {
    inverseRoundKeyAdd(unCypherText);
    inverseColumnMix(unCypherText);
    inverseRowShift(unCypherText);
    inverseByteSub(unCypherText);
}
void inverseFinalRound(unsigned char** unCypherText) {
    inverseRoundKeyAdd(unCypherText);
    inverseRowShift(unCypherText);
    inverseByteSub(unCypherText);
}

void deCrypt(unsigned char** unCypherText, unsigned char** cypherText) {
    inverseFinalRound(unCypherText);
    for (int i = 0; i < 10; i++) {
        inverseRound(unCypherText, cypherText);
    }
    inverseRoundKeyAdd(unCypherText);
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

    string line;
    string dat = "plainText.txt";
    ifstream stream;
    int n;

    stream.open(dat);
    getline(stream, line);
    stream.close();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tablicaPlainText[j][i] = line[4 * i + j];
            tablicaCypherText[j][i] = line[4 * i + j];
        }
    }

    dat = "kljuc.pem";

    stream.open(dat);
    getline(stream, line);
    stream.close();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            kljuc[j][i] = line[4 * i + j];
        }
    }
    keySchedule(kljuc, prosireniKljuc);

    crypt(tablicaCypherText, tablicaPlainText);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tablicaUnCypherText[i][j] = tablicaCypherText[i][j];
        }
    }
    deCrypt(tablicaUnCypherText, tablicaCypherText);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << (tablicaPlainText[j][i]) << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << (tablicaCypherText[j][i]) << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << (tablicaUnCypherText[j][i]) << " ";
        }
    }
    return 0;
}
