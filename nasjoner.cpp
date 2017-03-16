#include <iostream>

using namespace std;

#include "nasjoner.h"
#include "nasjon.h"

Nasjoner::Nasjoner()
{
	nasjonListe = new List(Sorted);
}

void Nasjoner::registrerNasjon()
{
	Nasjon* nyNasjon;
	char temp[LANDSKODE + 1];
	les("Landkode på formen XXX", temp, LANDSKODE);
	if (nasjonListe->noOfElements() < MAXNASJONER)
	{
		nyNasjon = new Nasjon(temp);
		nasjonListe->add(nyNasjon);
	}
	else
	{
		cout << "\n\tIkke plass til flere land." << endl;
	}
}

void Nasjoner::endreNasjon()
{
	Nasjon* tempNasjon;
	char temp[LANDSKODE + 1];

	les("Skriv inn landskode på nasjon du vil endre på", temp, LANDSKODE);
	if (nasjonListe->inList(temp))
	{
		tempNasjon = (Nasjon*)nasjonListe->remove(temp);
		tempNasjon->endreNasjon();
		nasjonListe->add(tempNasjon);
	}
	else
	{
		cout << "Ingen Nasjoner med denne landskoden!";
	}
}

