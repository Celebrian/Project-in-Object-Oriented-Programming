#include <iostream>
#include <fstream>
#include "statestikk.h"

void Statestikk::lesFraFil(ifstream & inn, int t) // får med antall nasjoner som paramenter
{
	for (int i = 1; i <= t; i++)	// looper gjennon til antall nasjoner
	{
		inn.getline(nasjonForkortelser[i],LANDSKODE);	// leser inn nasjonsforkortelsene i arrayen.
	}
}

void Statestikk::skrivTilFil(ofstream & ut)
{
	for (int i = 1; i <= sisteBrukt; i++)	// looper opp til antall nasjoner med poeng
	{
		ut << nasjonForkortelser[i] << '\n';	// skriver forkortelsene til fil.
	}
}
