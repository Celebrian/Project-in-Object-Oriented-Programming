#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>

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

void Medaljer::sorterMedaljer()
{

	for (int i = 1; i < sisteBrukt; i++) {						//Går gjenom alle untatt den siste
		for (int j = i + 1; j <= sisteBrukt; j++)				//Sammenligner med resten
		{
			if (medaljeListe[i][gull] == medaljeListe[j][gull])
			{													//Hvis i har flere gull en j
				if (medaljeListe[i][solv] == medaljeListe[j][solv])
				{
					if (medaljeListe[i][bronse] == medaljeListe[j][bronse])
					{
						if (strcmp(nasjonForkortelser[i], nasjonForkortelser[j]) < 0)
						{
							flytt(i, j);
						}
					}
					else if (medaljeListe[i][bronse] < medaljeListe[j][bronse])
					{
						flytt(i, j);
					}
				}
				else if (medaljeListe[i][solv] < medaljeListe[j][solv])
				{
					flytt(i, j);
				}
			}
			else if (medaljeListe[i][gull] < medaljeListe[j][gull])
			{
				flytt(i, j);
			}
		}
	}
}

void Medaljer::flytt(const int i, const int j)
{
	char land[LANDSKODE];
	int antMedaljer;

	strcpy(land, nasjonForkortelser[i]);
	strcpy(nasjonForkortelser[i], nasjonForkortelser[j]);    //i peker til j
	strcpy(nasjonForkortelser[j], land);			//j peker til temp(der i var)
	//GULL
	antMedaljer = medaljeListe[i][gull];
	medaljeListe[i][gull] = medaljeListe[j][gull];
	medaljeListe[j][gull] = antMedaljer;
	//SOLV
	antMedaljer = medaljeListe[i][solv];
	medaljeListe[i][solv] = medaljeListe[j][solv];
	medaljeListe[j][solv] = antMedaljer;
	//BRONSE
	antMedaljer = medaljeListe[i][bronse];
	medaljeListe[i][bronse] = medaljeListe[j][bronse];
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