
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

unsigned char rci[10];
unsigned int rconi[10];

void popuniRconi(void)
{
	rci[1] = 1;

	for (int i = 2; i <= 10; i++)
	{
		rci[i] = podijeliPolinomski(pomnoziPolinomski(2, rci[i - 1]), 0x11b);
		rconi[i] = 0 ^ rci[i] << 24;
	}
	cout << endl;
}

void keySchedule(unsigned char **kljuc, unsigned char **prosireniKljuc)
{
	cout << endl
		 << endl
		 << endl;
	cout << "KLJUC: " << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << hex << setw(2) << setfill('0') << (int)kljuc[j][i] << " ";
		}
	}
	cout << endl;

	popuniRconi();

	int n = 4;	// aes128
	int r = 11; // aes128 11 rundi

	for (int i = 0; i < 44; i++)
	{
		if (i < n)
		{
			for (int j = 0; j < 4; j++)
			{
				prosireniKljuc[i][j] = kljuc[j][i];
			}
		}
		else if (i >= n && i % n == 0)
		{
			unsigned char temp[4];
			for (int j = 0; j < 4; j++)
			{
				temp[j] = prosireniKljuc[i - 1][j];
			}

			posmakni(temp);
			for (int j = 0; j < 4; j++)
			{
				prosireniKljuc[i][j] =
					prosireniKljuc[i - n][j] ^ izSboxa(temp[j]) ^ (j == 0 ? rci[i / n] : 0);
			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				prosireniKljuc[i][j] = prosireniKljuc[i - n][j] ^ prosireniKljuc[i - 1][j];
			}
		}
	}
	/* cout << "prošireni" << endl;
	for (int i = 0; i < 44; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << hex << (int)prosireniKljuc[i][j] << " ";
		}
		if (i % 4 == 3)
		{
			cout << endl;
		}
	}
	cout << "prošireni" << endl; */
}

void RoundKeyAdd(unsigned char **cypherText, unsigned char **prosireniKljuc, int runda)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cypherText[i][j] = cypherText[i][j] ^ prosireniKljuc[runda * 4 + j][i];
		}
	}
}
void inverseRoundKeyAdd(unsigned char **cypherText, unsigned char **prosireniKljuc, int runda)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cypherText[i][j] = cypherText[i][j] ^ prosireniKljuc[runda * 4 + j][i];
		}
	}
}
