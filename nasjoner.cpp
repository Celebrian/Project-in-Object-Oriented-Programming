#include <iostream>

using namespace std;

#include "ListTool2B.h"
#include "nasjoner.h"
#include "nasjon.h"

Nasjoner::Nasjoner()
{
	nasjonListe = new List(Sorted);
}
void Nasjoner::skrivMenyN()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny nasjon";
	cout << "\n\tE = Endre en nasjon";
	cout << "\n\tA = Skriv alle data om alle nasjoner";
	cout << "\n\tT = Skriv en nasjons deltagertropp";
	cout << "\n\tS = Skriv alle data om en gitt nasjon";
	cout << "\n\tQ = Forrige meny";
}

void Nasjoner::MenyN()
{
	char valg;                //  Brukerens valg.
	skrivMenyN();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': registrerNasjon();			break;
		case 'E': endreNasjon();				break;
		case 'A': nasjonListe->displayList();	break;
		case 'T': cout << "\nSkriver tropp";	break;
		case 'S': skrivEnNasjon();;  break;
		default:  skrivMenyN();       break;
		}
		valg = les();
	}
}

void Nasjoner::registrerNasjon()
{
	Nasjon* nyNasjon;
	char temp[LANDSKODE + 1];
	if (nasjonListe->noOfElements() < MAXNASJONER)
	{
		lesNasjon("Landkode på formen XXX", temp, LANDSKODE);
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
	char temp[MAXTXT + 1];

	lesNasjon("Skriv inn landskode på nasjon du vil endre på", temp, LANDSKODE);
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

void Nasjoner::skrivEnNasjon()
{
	Nasjon* tempNasjon;
	char temp[LANDSKODE];
	do
	{
		lesNasjon("Skriv inn landskode som det skal skrives informasjon om", temp, LANDSKODE);
	} while (!nasjonListe->inList(temp));
	tempNasjon = (Nasjon*)nasjonListe->remove(temp);
	tempNasjon->display();
	nasjonListe->add(tempNasjon);
}

