
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

	string tip_aesa = argv[1];
	string enc_dec = argv[2];

	string datoteka_tekst = argv[3];
	string datoteka_kljuc = argv[4];

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
	unsigned char izlazna_datoteka[(cijela_datoteka.length() / 16) * 16 + 16];
	cout << "Duljina datoteke: " << dec << cijela_datoteka.length() << endl;
	cout << endl;

	cout << "ULAZNA DATOTEKA: " << endl;
	for (int i = 0; i < cijela_datoteka.length(); i++)
	{
		cout << hex << setfill('0') << setw(2) << (int)(unsigned char)cijela_datoteka[i] << " ";
		if (i % 16 == 15)
		{
			cout << endl;
		}
	}
	cout << endl;
	cout << endl;
	if (enc_dec == "ENK")
	{
		if (tip_aesa == "ECB")
		{
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.); i++)
			{
				// sto se ne popuni bit će nule
				unsigned char plaintext[16] = {};
				for (int j = 0; j < 16; j++)
				{
					if (i * 16 + j < cijela_datoteka.length())
					{
						plaintext[j] = cijela_datoteka[i * 16 + j];
					}
				}
				popuniTablicuPlaintextom(tablicaTeksta, plaintext);
				crypt(tablicaTeksta, prosireniKljuc);

				for (int m = 0; m < 4; m++)
				{
					for (int n = 0; n < 4; n++)
					{
						izlazna_datoteka[i * 16 + m * 4 + n] = tablicaTeksta[n][m];
					}
				}
			}
			cout << "ENKRIPTIRANA DATOTEKA ECB" << endl;
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.) * 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)izlazna_datoteka[i] << " ";
				if (i % 16 == 15)
				{
					cout << endl;
				}
			}
		}
		else if (tip_aesa == "CBC")
		{ /* 
			cout << "CBC" << endl; */
			unsigned char inic_vektor[16];

			// pročitaj prvih 16 znakova datoteke kao iv
			if (argc != 6)
			{
				cout << "Neispravan broj argumenata za CBC, tekst, kljuc, iv" << endl;
				return 0;
			}

			string datoteka_iv = argv[5];
			ifstream MyReadIVFile(datoteka_iv);
			for (int i = 0; i < 16; i++)
			{
				char znakic = 0;
				MyReadIVFile.get(znakic);
				inic_vektor[i] = znakic;
			}
			MyReadIVFile.close();

			cout << "Inicijalizacijski vektor: " << endl;
			for (int i = 0; i < 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)inic_vektor[i] << " ";
			}
			cout << endl;
			cout << endl;

			// sto se ne popuni bit će nule
			unsigned char plaintext[16] = {};
			for (int j = 0; j < 16; j++)
			{
				if (0 * 16 + j < cijela_datoteka.length())
				{
					plaintext[j] = cijela_datoteka[0 * 16 + j];
				}
			}
			for (int i = 0; i < 16; i++)
			{
				plaintext[i] = plaintext[i] ^ inic_vektor[i];
			}

			popuniTablicuPlaintextom(tablicaTeksta, plaintext);

			crypt(tablicaTeksta, prosireniKljuc);

			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					izlazna_datoteka[0 * 16 + m * 4 + n] = tablicaTeksta[n][m];
				}
			}
			for (int i = 1; i < ceil(cijela_datoteka.length() / 16.); i++)
			{
				unsigned char plaintext[16] = {};
				for (int j = 0; j < 16; j++)
				{
					if (i * 16 + j < cijela_datoteka.length())
					{
						plaintext[j] = cijela_datoteka[i * 16 + j];
					}
				}
				for (int k = 0; k < 4; k++)
				{
					for (int l = 0; l < 4; l++)
					{
						plaintext[k * 4 + l] = plaintext[k * 4 + l] ^ tablicaTeksta[l][k];
					}
				}

				popuniTablicuPlaintextom(tablicaTeksta, plaintext);

				crypt(tablicaTeksta, prosireniKljuc);

				for (int m = 0; m < 4; m++)
				{
					for (int n = 0; n < 4; n++)
					{
						izlazna_datoteka[i * 16 + m * 4 + n] = tablicaTeksta[n][m];
					}
				}
			}
			cout << "ENKRIPTIRANA DATOTEKA CBC" << endl;
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.) * 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)izlazna_datoteka[i] << " ";
				if (i % 16 == 15)
				{
					cout << endl;
				}
			}
		}
	}
	else if (enc_dec == "DEK")
	{
		if (tip_aesa == "ECB")
		{
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.); i++)
			{
				// sto se ne popuni bit će nule
				unsigned char plaintext[16] = {};
				for (int j = 0; j < 16; j++)
				{
					if (i * 16 + j < cijela_datoteka.length())
					{
						plaintext[j] = cijela_datoteka[i * 16 + j];
					}
				}
				popuniTablicuPlaintextom(tablicaTeksta, plaintext);
				deCrypt(tablicaTeksta, prosireniKljuc);

				for (int m = 0; m < 4; m++)
				{
					for (int n = 0; n < 4; n++)
					{
						izlazna_datoteka[i * 16 + m * 4 + n] = tablicaTeksta[n][m];
					}
				}
			}
			cout << "DEKRIPTIRANA DATOTEKA ECB" << endl;
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.) * 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)izlazna_datoteka[i] << " ";
				if (i % 16 == 15)
				{
					cout << endl;
				}
			}
		}
		else if (tip_aesa == "CBC")
		{ /* 
			cout << "CBC" << endl; */
			unsigned char inic_vektor[16];

			// pročitaj prvih 16 znakova datoteke kao iv
			if (argc != 6)
			{
				cout << "Neispravan broj argumenata za CBC DEK, tekst, kljuc, iv " << argc << endl;
				return 0;
			}

			string datoteka_iv = argv[5];
			ifstream MyReadIVFile(datoteka_iv);
			for (int i = 0; i < 16; i++)
			{
				char znakic = 0;
				MyReadIVFile.get(znakic);
				inic_vektor[i] = znakic;
			}
			MyReadIVFile.close();

			cout << "Inicijalizacijski vektor: " << endl;
			for (int i = 0; i < 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)inic_vektor[i] << " ";
			}
			cout << endl;
			cout << endl;

			// sto se ne popuni bit će nule
			unsigned char ciphertext[16] = {};
			for (int j = 0; j < 16; j++)
			{
				if (0 * 16 + j < cijela_datoteka.length())
				{
					ciphertext[j] = cijela_datoteka[0 * 16 + j];
				}
			}

			popuniTablicuPlaintextom(tablicaTeksta, ciphertext);

			deCrypt(tablicaTeksta, prosireniKljuc);
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					tablicaTeksta[l][k] = tablicaTeksta[l][k] ^ inic_vektor[k * 4 + l];
				}
			}

			for (int m = 0; m < 4; m++)
			{
				for (int n = 0; n < 4; n++)
				{
					izlazna_datoteka[0 * 16 + m * 4 + n] = tablicaTeksta[n][m];
				}
			}
			for (int i = 1; i < ceil(cijela_datoteka.length() / 16.); i++)
			{
				unsigned char ciphertext[16] = {};
				for (int j = 0; j < 16; j++)
				{
					if (i * 16 + j < cijela_datoteka.length())
					{
						ciphertext[j] = cijela_datoteka[i * 16 + j];
					}
				}

				popuniTablicuPlaintextom(tablicaTeksta, ciphertext);

				deCrypt(tablicaTeksta, prosireniKljuc);

				for (int k = 0; k < 4; k++)
				{
					for (int l = 0; l < 4; l++)
					{
						tablicaTeksta[l][k] = cijela_datoteka[(i - 1) * 16 + k * 4 + l] ^ tablicaTeksta[l][k];
					}
				}

				for (int m = 0; m < 4; m++)
				{
					for (int n = 0; n < 4; n++)
					{
						izlazna_datoteka[i * 16 + m * 4 + n] = tablicaTeksta[n][m];
					}
				}
			}
			cout << endl;
			cout << "DEKRIPTIRANA DATOTEKA CBC" << endl;
			for (int i = 0; i < ceil(cijela_datoteka.length() / 16.) * 16; i++)
			{
				cout << hex << setfill('0') << setw(2) << (int)(unsigned char)izlazna_datoteka[i] << " ";
				if (i % 16 == 15)
				{
					cout << endl;
				}
			}
		}
	}

	cout << endl
		 << endl;

	return 0;
}