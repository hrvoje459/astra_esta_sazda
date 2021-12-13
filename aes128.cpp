
#include "aesHeader.h"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

// KRIPTIRANJE

void round(unsigned char **plainText, unsigned char **prosireniKljuc, int i)
{
	byteSub(plainText);
	rowShift(plainText);
	columnMix(plainText);
	RoundKeyAdd(plainText, prosireniKljuc, i);
}
void finalRound(unsigned char **plainText, unsigned char **prosireniKljuc, int i)
{
	byteSub(plainText);
	rowShift(plainText);
	RoundKeyAdd(plainText, prosireniKljuc, i);
}
void crypt(unsigned char **plainText, unsigned char **prosireniKljuc)
{
	int i = 0;
	RoundKeyAdd(plainText, prosireniKljuc, i);
	for (i = 1; i < 10; i++)
	{
		round(plainText, prosireniKljuc, i);
	}
	finalRound(plainText, prosireniKljuc, i);
}

// DEKRIPTIRANJE
void inverseRound(unsigned char **cypherText, unsigned char **prosireniKljuc, int i)
{
	inverseRoundKeyAdd(cypherText, prosireniKljuc, i);
	inverseColumnMix(cypherText);
	inverseRowShift(cypherText);
	inverseByteSub(cypherText);
}
void inverseFinalRound(unsigned char **cypherText, unsigned char **prosireniKljuc, int i)
{
	inverseRoundKeyAdd(cypherText, prosireniKljuc, i);
	inverseRowShift(cypherText);
	inverseByteSub(cypherText);
}

void deCrypt(unsigned char **cypherText, unsigned char **prosireniKljuc)
{
	int i = 10;
	inverseFinalRound(cypherText, prosireniKljuc, i);
	for (i = 9; i > 0; i--)
	{
		inverseRound(cypherText, prosireniKljuc, i);
	}
	inverseRoundKeyAdd(cypherText, prosireniKljuc, i);
}
