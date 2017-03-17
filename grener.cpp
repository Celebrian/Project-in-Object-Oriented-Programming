#include <iostream>

using namespace std;

#include "grener.h"
#include "funksjoner.h"
#include "const.h"
#include "gren.h"

Grener::Grener()
{
	grenListe = new List(Sorted);
}

void Grener::lagNyGren()
{
	char* temp;
	do
	{
		les("\nSkriv inn navn på gren: ", temp);
	} while (grenListe->inList(temp));
	if (grenListe->noOfElements() < MAXDELTAGER)
	{
		Gren* nyGren;
		nyGren = new Gren(temp);
		grenListe->add(nyGren);
		sisteGren++;
	}
}

void Grener::endreGren()
{
	Gren* temppeker;
	char*  temp;
	les("\nSkriv inn navn på gren du vil endre: ", temp);
	if (grenListe->inList(temp))
	{
		temppeker = (Gren*)grenListe->remove(temp);
		temppeker->endreNyGren();
		grenListe->add(temppeker);
		sisteGren++;
	}
	else {
		cout << "\nDeltager finnes ikke." << endl;
	}
}

void Grener::skrivUt()
{
	grenListe->displayList();
}

void Grener::skrivUtValgt()
{
	// GJØR DETTE ETTER O ER FERDIG.
}
