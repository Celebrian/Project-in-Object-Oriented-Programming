#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <cstring>
#include <iostream>

using namespace std; 

#include "poeng.h"

void Poeng::oppdaterPoeng(char ch[LANDSKODE], int antP)
{
	bool b = false;   // For å sjekke om nasjon finnes
	int temp;
	for (int  i = 1; i <= sisteBrukt; i++)	// looper gjennom alle nasjoner i statistikk
	{
		if (!strcmp(nasjonForkortelser[i], ch))	// Sjekker om den finner nasjonen brukeren skrev in
		{
			temp = i;
			poengOversikt[temp] = antP;	// legger poeng inn på samme sted i poengarray som nasjon ligger i statistikk sin array
			b = true;		// Nasjonen fines
		}
	}
	if (!b)		// hvis nasjon ikke finnes  statistikk array
	{
		strcpy(nasjonForkortelser[++sisteBrukt], ch);	// legger nasjonen inn i statistikkarray
		temp = sisteBrukt;
		poengOversikt[temp] = antP; // legger poeng inn i poengarray.
	}
	sorterPoeng();
}

void Poeng::sorterPoeng()
{
	for (int i = 1; i <= sisteBrukt; i++)
	{ // teller off for den første arrayskuffen.
		for (int j = i + 1; j <= sisteBrukt; j++)
		{// teller opp den andre arrayskuffen.
			if (poengOversikt[i] < poengOversikt[j])
			{// hvis skuff i sitt nummer er mindre enn j.
				int temp = poengOversikt[i];
				poengOversikt[i] = poengOversikt[j];
				poengOversikt[j] = temp;
				char temp2[LANDSKODE];
				strcpy(temp2,nasjonForkortelser[i]);
				strcpy(nasjonForkortelser[i], nasjonForkortelser[j]);
				strcpy(nasjonForkortelser[j], temp2);
				// bytt omm i og j sine indexer i arrayen.
			}
		}
	}
}

void Poeng::displayPoeng() // TESTFUNKSJON, SKAL SLETTES SENERE.
{
	for (int i = 1; i <= sisteBrukt; i++)
	{
		cout << "\nNasjon: " << nasjonForkortelser[i] << " Har : " << poengOversikt[i] << " Poeng." << endl;
	}
}