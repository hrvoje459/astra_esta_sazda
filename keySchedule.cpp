
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

unsigned char rci[10];
unsigned int rconi[10];

void popuniRconi(void) {
    rci[1] = 1;

    for (int i = 2; i <= 10; i++) {
        rci[i] = podijeliPolinomski(pomnoziPolinomski(2, rci[i - 1]), 0x11b);
        rconi[i] = 0 ^ rci[i] << 24;
        // cout << bitset<32>(rci[i]) << "  " << hex << rci[i] << endl;
        // cout << bitset<32>(rconi[i]) << endl;
    }
    /* for (int i = 1; i <= 10; i++) {
        cout << hex << (int)(rci[i]) << "  ";
    } */
    cout << endl;
}

void keySchedule(unsigned char** kljuc, unsigned char** prosireniKljuc) {
    cout << "kljuc: " << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            /*  kljuc[0][0] = 0x49;
             kljuc[0][1] = 0x20;
             kljuc[0][2] = 0xe2;
             kljuc[0][3] = 0x99;

             kljuc[1][0] = 0xa5;
             kljuc[1][1] = 0x20;
             kljuc[1][2] = 0x52;
             kljuc[1][3] = 0x61;

             kljuc[2][0] = 0x64;
             kljuc[2][1] = 0x69;
             kljuc[2][2] = 0x6f;
             kljuc[2][3] = 0x47;

             kljuc[3][0] = 0x61;
             kljuc[3][1] = 0x74;
             kljuc[3][2] = 0x75;
             kljuc[3][3] = 0x6e; */

            cout << hex << setw(2) << setfill('0') << (kljuc[j][i]) << " ";
        }
    }
    cout << endl;

    popuniRconi();

    int n = 4;  // aes128
    int r = 11; // aes128 11 rundi

    for (int i = 0; i < 44; i++) {
        if (i < n) {
            for (int j = 0; j < 4; j++) {
                prosireniKljuc[i][j] = kljuc[i][j];
            }
        } else if (i >= n && i % n == 0) {
            unsigned char temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = prosireniKljuc[i - 1][j];
            }

            posmakni(temp);
            for (int j = 0; j < 4; j++) {
                prosireniKljuc[i][j] =
                    prosireniKljuc[i - n][j] ^ izSboxa(temp[j]) ^ (j == 0 ? rci[i / n] : 0);
            }
        } else if (i >= n && n > 6 && i % n == 4) {
            for (int j = 0; j < 4; j++) {
                prosireniKljuc[i][j] = prosireniKljuc[i - n][j] ^ izSboxa(prosireniKljuc[i - 1][j]);
            }
        } else {
            for (int j = 0; j < 4; j++) {
                prosireniKljuc[i][j] = prosireniKljuc[i - n][j] ^ prosireniKljuc[i - 1][j];
            }
        }
    }

    cout << "Prosireni kljuc: " << endl;
    for (int i = 0; i < 44; i++) {
        if (i % 4 == 0) {
            cout << endl;
        }
        // cout << dec << "w[" << setw(2) << setfill('0') << i << "] ";
        for (int j = 0; j < 4; j++) {
            cout << hex << setw(2) << setfill('0') << int(prosireniKljuc[i][j]) << " ";
        }
        // cout << endl;
    }
    cout << endl << endl;
}

void RoundKeyAdd(unsigned char** cypherText) {}
void inverseRoundKeyAdd(unsigned char** cypherText) {}
