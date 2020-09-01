#include <fstream>
#include <iostream>
using namespace std;

unsigned char SBox[256] = {
    99,  124, 119, 123, 242, 107, 111, 197, 48,  1,   103, 43,  254, 215, 171, 118, 202, 130, 201,
    125, 250, 89,  71,  240, 173, 212, 162, 175, 156, 164, 114, 192, 183, 253, 147, 38,  54,  63,
    247, 204, 52,  165, 229, 241, 113, 216, 49,  21,  4,   199, 35,  195, 24,  150, 5,   154, 7,
    18,  128, 226, 235, 39,  178, 117, 9,   131, 44,  26,  27,  110, 90,  160, 82,  59,  214, 179,
    41,  227, 47,  132, 83,  209, 0,   237, 32,  252, 177, 91,  106, 203, 190, 57,  74,  76,  88,
    207, 208, 239, 170, 251, 67,  77,  51,  133, 69,  249, 2,   127, 80,  60,  159, 168, 81,  163,
    64,  143, 146, 157, 56,  245, 188, 182, 218, 33,  16,  255, 243, 210, 205, 12,  19,  236, 95,
    151, 68,  23,  196, 167, 126, 61,  100, 93,  25,  115, 96,  129, 79,  220, 34,  42,  144, 136,
    70,  238, 184, 20,  222, 94,  11,  219, 224, 50,  58,  10,  73,  6,   36,  92,  194, 211, 172,
    98,  145, 149, 228, 121, 231, 200, 55,  109, 141, 213, 78,  169, 108, 86,  244, 234, 101, 122,
    174, 8,   186, 120, 37,  46,  28,  166, 180, 198, 232, 221, 116, 31,  75,  189, 139, 138, 112,
    62,  181, 102, 72,  3,   246, 14,  97,  53,  87,  185, 134, 193, 29,  158, 225, 248, 152, 17,
    105, 217, 142, 148, 155, 30,  135, 233, 206, 85,  40,  223, 140, 161, 137, 13,  191, 230, 66,
    104, 65,  153, 45,  15,  176, 84,  187, 22};

unsigned char SBoxInverse[256] = {
    82,  9,   106, 213, 48,  54,  165, 56,  191, 64,  163, 158, 129, 243, 215, 251, 124, 227, 57,
    130, 155, 47,  255, 135, 52,  142, 67,  68,  196, 222, 233, 203, 84,  123, 148, 50,  166, 194,
    35,  61,  238, 76,  149, 11,  66,  250, 195, 78,  8,   46,  161, 102, 40,  217, 36,  178, 118,
    91,  162, 73,  109, 139, 209, 37,  114, 248, 246, 100, 134, 104, 152, 22,  212, 164, 92,  204,
    93,  101, 182, 146, 108, 112, 72,  80,  253, 237, 185, 218, 94,  21,  70,  87,  167, 141, 157,
    132, 144, 216, 171, 0,   140, 188, 211, 10,  247, 228, 88,  5,   184, 179, 69,  6,   208, 44,
    30,  143, 202, 63,  15,  2,   193, 175, 189, 3,   1,   19,  138, 107, 58,  145, 17,  65,  79,
    103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115, 150, 172, 116, 34,  231, 173, 53,  133,
    226, 249, 55,  232, 28,  117, 223, 110, 71,  241, 26,  113, 29,  41,  197, 137, 111, 183, 98,
    14,  170, 24,  190, 27,  252, 86,  62,  75,  198, 210, 121, 32,  154, 219, 192, 254, 120, 205,
    90,  244, 31,  221, 168, 51,  136, 7,   199, 49,  177, 18,  16,  89,  39,  128, 236, 95,  96,
    81,  127, 169, 25,  181, 74,  13,  45,  229, 122, 159, 147, 201, 156, 239, 160, 224, 59,  77,
    174, 42,  245, 176, 200, 235, 187, 60,  131, 83,  153, 97,  23,  43,  4,   126, 186, 119, 214,
    38,  225, 105, 20,  99,  85,  33,  12,  125};
unsigned char mullTable[4][4] = {{2, 3, 1, 1}, {1, 2, 3, 1}, {1, 1, 2, 3}, {3, 1, 1, 2}};
unsigned char inverseMullTable[4][4] = {{14, 11, 13, 9}, {9, 14, 11, 13}, {13, 9, 14, 11}, {11, 13, 9, 14}};

unsigned char galoisMull(unsigned char b) {
    if (b >= 128) {
        b = b << 1;
        b ^= 0x1B;
    } else {
        b = b << 1;
    }
    return b;
}
unsigned char puta_X(int mult, unsigned char b) {
    unsigned char out;
    switch (mult) {
    case 1:
        out = b;
        break;
    case 2:
        out = galoisMull(b);
        break;
    case 3:
        out = galoisMull(b) ^ b;
        break;
    case 9:
        out = galoisMull(galoisMull(galoisMull(b))) ^ b;
        break;
    case 11:
        out = galoisMull(galoisMull(galoisMull(b)) ^ b) ^ b;
        break;
    case 13:
        out = galoisMull(galoisMull(galoisMull(b) ^ b)) ^ b;
        break;
    case 14:
        out = galoisMull(galoisMull(galoisMull(b) ^ b) ^ b);
        break;
    }
    return out;
}
// SUBSTITUIRAJ
void byteSub(unsigned char** cypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cypherText[i][j] = SBox[cypherText[i][j]];
        }
    }
}
void inverseByteSub(unsigned char** cypherText) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cypherText[i][j] = SBoxInverse[cypherText[i][j]];
        }
    }
}

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
                temp ^= puta_X(mullTable[i][j], helperArray[j]);
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
                temp ^= puta_X(inverseMullTable[i][j], helperArray[j]);
            }
            unCypherText[i][k] = temp;
        }
    }
}

// DODAJ KLJUCEVE
void RoundKeyAdd(unsigned char** cypherText) {}

void inverseRoundKeyAdd(unsigned char** cypherText) {}

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

    tablicaPlainText = new unsigned char*[4];
    tablicaCypherText = new unsigned char*[4];
    tablicaUnCypherText = new unsigned char*[4];

    for (int i = 0; i < 4; i++) {
        tablicaPlainText[i] = new unsigned char[4];
        tablicaCypherText[i] = new unsigned char[4];
        tablicaUnCypherText[i] = new unsigned char[4];
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
