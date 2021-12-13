
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>

using namespace std;

void popuniTablicuPlaintextom(unsigned char **tablicaTeksta, unsigned char nekiPlainText[])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tablicaTeksta[j][i] = nekiPlainText[i * 4 + j];
		}
	}
}
void popuniKljucicTablicu(unsigned char **tablicaKljucica, unsigned char * /* string */ kljucic)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tablicaKljucica[j][i] = kljucic[i * 4 + j];
		}
	}
}

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		cout << "Neispravan broj argumenta, program prima redom, tekstualnu datoteku čiji sadržaj treba enkriptirati i ključ" << endl;
		return 0;
	}

	string datoteka_tekst = argv[1];
	string datoteka_kljuc = argv[2];

	cout << "Datoteka tekst: " << datoteka_tekst << endl;
	cout << "Datoteka kljuc: " << datoteka_kljuc << endl;

	// Pročitaj prvih 16 znakova iz datoteke kao kljuc

	unsigned char kljucic[16];

	ifstream MyReadKeyFile(datoteka_kljuc);
	for (int i = 0; i < 16; i++)
	{
		char znakic = 0;
		MyReadKeyFile.get(znakic);
		kljucic[i] = znakic;
	}
	MyReadKeyFile.close();

	unsigned char **tablicaTeksta;

	unsigned char **tablicaKljucica;
	unsigned char **prosireniKljuc;

	tablicaTeksta = new unsigned char *[4];
	tablicaKljucica = new unsigned char *[4];

	prosireniKljuc = new unsigned char *[44];

	for (int i = 0; i < 4; i++)
	{
		tablicaTeksta[i] = new unsigned char[4];
		tablicaKljucica[i] = new unsigned char[4];
	}

	for (int i = 0; i < 44; i++)
	{
		prosireniKljuc[i] = new unsigned char[4];
	}

	popuniKljucicTablicu(tablicaKljucica, kljucic);
	keySchedule(tablicaKljucica, prosireniKljuc);

	// Pročitaj datoteku u string
	ifstream MyReadTekstFile(datoteka_tekst);
	string cijela_datoteka = "";
	char znakic = 0;
	while (MyReadTekstFile.get(znakic))
	{
		cijela_datoteka += znakic;
	}
	unsigned char enkriptirana_datoteka[cijela_datoteka.length()];

	for (int i = 0; i <= ceil(cijela_datoteka.length() / 16); i++)
	{
		cout << "CRYPT " << i << "==" << endl;
		// sto se ne popuni bit će nule
		unsigned char plaintext[16] = {};
		for (int j = 0; j < 16; j++)
		{
			if (i * 16 + j < cijela_datoteka.length())
			{
				plaintext[j] = cijela_datoteka[i * 16 + j];
			}
		}
		cout << "Plaintext array:" << endl;
		for (int k = 0; k < 16; k++)
		{
			cout << plaintext[k] << " ";
		}
		cout << endl;

		popuniTablicuPlaintextom(tablicaTeksta, plaintext);
		crypt(tablicaTeksta, prosireniKljuc);

		for (int m = 0; m < 4; m++)
		{
			for (int n = 0; n < 4; n++)
			{
				cout << hex << (int)tablicaTeksta[n][m] << " ";
			}
		}
		cout << endl;

		for (int m = 0; m < 4; m++)
		{
			for (int n = 0; n < 4; n++)
			{
				enkriptirana_datoteka[i * 16 + m * 4 + n] = tablicaTeksta[n][m];
			}
		}
	}
	cout << "ENKRIPTIRANA DATOTEKA" << endl;
	for (int i = 0; i <= cijela_datoteka.length(); i++)
	{
		cout << hex << (int)enkriptirana_datoteka[i] << " ";
		if (i % 16 == 15)
		{
			cout << endl;
		}
	}

	cout << endl;
	/*unsigned char tekst[] = "0123456789ABCDEF";*/
	/* unsigned char kljucic[] = "0123456789ABCDEF"; */

	/*popuniTablicuPlaintextom(tablicaTeksta, tekst);*/

	// tablica teksta prije kriptiranja (PLAINTEXT)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << hex << (int)(tablicaTeksta[j][i]) << " ";
		}
	}
	cout << endl;

	crypt(tablicaTeksta, prosireniKljuc);

	// tablica teksta poslije kriptiranja (ENCRYPTED)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << hex << (int)(tablicaTeksta[j][i]) << " ";
		}
	}
	cout << endl;

	deCrypt(tablicaTeksta, prosireniKljuc);

	// tablica teksta poslije dekriptiranja (DECRYPTED)
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << hex << (int)(tablicaTeksta[j][i]) << " ";
		}
	}

	cout << endl;

	return 0;
}