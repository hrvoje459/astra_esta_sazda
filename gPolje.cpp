#include <bitset>
#include <fstream>
#include <iostream>

using namespace std;

int vodeciKoeficijent(unsigned short int polinom) {
    for (int i = 0; i < 16; i++) {
        if (polinom & 1 << (15 - i)) {
            return 15 - i;
        }
    }
    return 0;
}

unsigned short int pomnoziPolinomski(unsigned short int a, unsigned short int b) {
    unsigned short int umnozak = 0;

    bool bitPrvog = 0;
    bool bitDrugog = 0;

    for (int i = 0; i < 16; i++) {
        bitPrvog = a & (1 << i);
        for (int j = 0; j < 16; j++) {
            bitDrugog = b & (1 << j);
            bitDrugog = bitDrugog && bitPrvog;

            if (bitDrugog) {
                if (umnozak & (1 << (i + j)) && (1 << (i + j))) {
                    umnozak = umnozak & ~(1 << (i + j));
                } else {
                    umnozak = umnozak | (1 << (i + j));
                }
            }
        }
    }

    return umnozak;
}

unsigned short int podijeliPolinomski(unsigned short int djeljenik, unsigned short int djelitelj) {
    unsigned short int ostatak = djeljenik;

    int vodeciKoeficijentModula = vodeciKoeficijent(djelitelj);

    for (int i = 0; i < 16; i++) {
        if (ostatak & (1 << (15 - i))) {
            ostatak = ostatak ^ pomnoziPolinomski(djelitelj, 1 << (vodeciKoeficijent(ostatak) - vodeciKoeficijentModula));
        }
    }
    return ostatak;
}

unsigned short int gPoljePomnozi(unsigned short a, unsigned short b) {
    return podijeliPolinomski(pomnoziPolinomski(a, b), 0x011b);
}
unsigned char gPoljeZbroji(unsigned char a, unsigned char b) { return a ^ b; }


// generiranje konstanti runde

/* int main(void) {
    unsigned short int p = 1;

    for (int i = 0; i < 30; i++) {
        cout << hex << p << endl;
        p = podijeliPolinomski(pomnoziPolinomski(2, p), 0x11b);
    }

    return 0;
} */
