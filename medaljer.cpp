#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

#include "enum.h"
#include "medaljer.h"

void Medaljer::nyMedalje(const char land[LANDSKODE], const medalje pris)
{
	bool finnes = false;										//Antar att landet ikke finnes
	for (int i = 1; i <= sisteBrukt; i++)
	{
		if (!strcmp(land, nasjonForkortelser[i]))				//Sammenlikner med land
		{
			medaljeListe[i][pris]++;							//Teller opp medalje
			finnes = true;										//Fant land
		}
	}
	if (!finnes)												//Hvis land ikke ble funnet
	{
		strcpy(nasjonForkortelser[++sisteBrukt], land);			//Legger inn nytt land
		medaljeListe[sisteBrukt][pris]++;						//Legger til medaljen
	}
	sorterMedaljer();
}

void Medaljer::sorterMedaljer()									//Sorterer medaljer
{

	for (int i = 1; i < sisteBrukt; i++) {						//Går gjenom alle untatt den siste
		for (int j = i + 1; j <= sisteBrukt; j++)				//Sammenligner med resten
		{
			if (medaljeListe[i][gull] == medaljeListe[j][gull])	//Hvis I har like mange gull som J, skjekk
			{
				if (medaljeListe[i][solv] == medaljeListe[j][solv])	//Hvis I har like mange Sølv som J, skjekk
				{
					if (medaljeListe[i][bronse] == medaljeListe[j][bronse])	//Hvis I har like mange bronse som J:
					{
						if (strcmp(nasjonForkortelser[i], nasjonForkortelser[j]) < 0)	//Sorter på Landskode
						{
							bytt(i, j);			//Hvis de har like mange gull, sølv og bronse, sorter på landskode
						}
					}
					else if (medaljeListe[i][bronse] < medaljeListe[j][bronse])	//Hvis gull og sølv er like og
					{
						bytt(i, j);				//Bronse er forskjellig, bytt den med minst bakover
					}
				}
				else if (medaljeListe[i][solv] < medaljeListe[j][solv])	//Hvis gull er lik og 
				{
					bytt(i, j);					//Sølv er forskjellig, bytt den med minst bakover
				}
			}
			else if (medaljeListe[i][gull] < medaljeListe[j][gull])	//Hvis gull er forskjellig
			{
				bytt(i, j);						//Bytt den med minst bakover
			}
		}
	}
}

void Medaljer::bytt(const int i, const int j)
{
	char land[LANDSKODE];
	int antMedaljer;

	strcpy(land, nasjonForkortelser[i]);						//Kopierer I over i temp
	strcpy(nasjonForkortelser[i], nasjonForkortelser[j]);		//Flytter J over I
	strcpy(nasjonForkortelser[j], land);						//Flytter temp over J
	//GULL
	antMedaljer = medaljeListe[i][gull];						//Flytter gull fra I over i antMedaljer
	medaljeListe[i][gull] = medaljeListe[j][gull];				//Flytter J gull over I gull
	medaljeListe[j][gull] = antMedaljer;						//Flytter antMedaljer over J gull
	//SOLV
	antMedaljer = medaljeListe[i][solv];
	medaljeListe[i][solv] = medaljeListe[j][solv];				//Samme som for gull, bare sølv
	medaljeListe[j][solv] = antMedaljer;
	//BRONSE
	antMedaljer = medaljeListe[i][bronse];
	medaljeListe[i][bronse] = medaljeListe[j][bronse];			//Og igjen samme for bronse
	medaljeListe[j][bronse] = antMedaljer;
}

void Medaljer::visMedaljer()
{
	for (int i = 1; i <= sisteBrukt; i++)
	{
		cout << "\n\tNasjon: " << nasjonForkortelser[i] << " har Gull: " << medaljeListe[i][gull] 
			<< " Sølv: " << medaljeListe[i][solv] << " Bronse: " << medaljeListe[i][bronse] << endl;
	}
}

void Medaljer::lesMedaljerFraFil()
{
	ifstream inn("gruppe03/MEDALJER.DTA");
	if (inn)
	{
		inn >> sisteBrukt; inn.ignore();
		Statestikk::lesFraFil(inn, sisteBrukt);
		for (int i = 1; i <= sisteBrukt; i++)
		{
			inn >> medaljeListe[i][gull] >> medaljeListe[i][solv] >> medaljeListe[i][bronse]; inn.ignore();
		}
	}
}

void Medaljer::skrivMedaljerTilFil()
{
	ofstream ut("gruppe03/MEDALJER.DTA");
	ut << sisteBrukt << endl;
	Statestikk::skrivTilFil(ut);
	for (int i = 0; i < sisteBrukt; i++)
	{
		ut << medaljeListe[i][gull] << " "
			<< medaljeListe[i][solv] << " "
			<< medaljeListe[i][bronse] << endl;
	}
}