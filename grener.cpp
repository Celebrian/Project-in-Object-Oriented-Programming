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

void Grener::MenyH()
{
	
		char valg;                //  Brukerens valg.
		skrivMenyG();                  //  skriver ut meny med valg.

		valg = les();             //  Leser brukerens valg.
		while (valg != 'Q') {
			switch (valg) {
			case 'N': lagNyGren(); ; break;
			case 'E': endreGren();  break;
			case 'A': skrivUt(); break;
			case 'S': skrivUtValgt();  break;
			default:  skrivMenyG();       break;
			}
			valg = les();
	}
}

void Grener::skrivMenyG()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny gren";
	cout << "\n\tE = Endre en gren";
	cout << "\n\tA = Skriv alle data om alle grener";
	cout << "\n\tS = Skriv alle data om en gitt gren";
	cout << "\n\tQ = Forrige meny";
}
