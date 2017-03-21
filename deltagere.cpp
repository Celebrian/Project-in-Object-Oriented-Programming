#include <iostream>
#include <fstream>

using namespace std;

#include "deltagere.h"
#include "funksjoner.h"
#include "const.h"
#include "deltager.h"

Deltagere::Deltagere()
{
	deltagerListe = new List(Sorted); // lager en ny liste med deltagere.
}

void Deltagere::lagNyDeltager()
{
	int temp;
	do
	{	// leser inn og sjekker om et deltagernummer er gyldig.
		temp = les("\nSkriv inn deltagernummer", MINDELTAGERE, MAXDELTAGERE);
	} while (deltagerListe->inList(temp));
		if (deltagerListe->noOfElements() < MAXDELTAGERE)	// hvis lista ikk er full.
	{
		Deltager* nyDeltager;	// så lages det et nytt deltagerobjekt
		nyDeltager = new Deltager(temp);	// og legger det inn i lista
		deltagerListe->add(nyDeltager);		// baser på innskrevet nummer.
		sisteDeltager++;	// teller opp variabelen.
	}
}

void Deltagere::endreDeltager()
{
	Deltager* temppeker;
	int temp; // leser inn nummer på deltager du vil endre.
	temp = les("\nSkriv inn deltagernummer", MINDELTAGERE, MAXDELTAGERE);
		if (deltagerListe->inList(temp)) //sjekker om deltager finnes.
		{
			temppeker = (Deltager*)deltagerListe->remove(temp);
			temppeker->endreNyDeltager();
			deltagerListe->add(temppeker);
			// tar den ut av liste, endrer på den, også legger den inn igjen.
		}
		else {
			cout << "\nDeltager finnes ikke." << endl;
		}
}

void Deltagere::skrivUt()
{
	if (!deltagerListe->isEmpty()) {
		deltagerListe->displayList();
	}
	else
	{
		cout << "\n\tIngen elementer i liste. " << endl;
	}
	// bruker en virtuel display funksjon til å skrive ut data om alle objekter.
}

void Deltagere::skrivUtValgt()
{
	Deltager* temppeker;
	int temp; // leser inn nummer på deltager du vil se data om.
	temp = les("\nSkriv inn deltagernummer", MINDELTAGERE, MAXDELTAGERE);
	if (deltagerListe->inList(temp))	// sjekker om deltageren finnes.
	{
		temppeker = (Deltager*)deltagerListe->remove(temp);
		temppeker->displayAll();
		deltagerListe->add(temppeker);
		// tar deltager ut av lista, displayer den, og setter den inn igjen.
	}
	else {
		cout << "\nDeltager finnes ikke." << endl;
	}
}

void Deltagere::loopGjennom(char ch[LANDSKODE+1])
{
	Deltager* temppeker;
	int temp = deltagerListe->noOfElements(); // henter antall elementer i lista.
	for (int i = 1; i <= temp; i++) // looper gjennom alle.
	{
		temppeker = (Deltager*)deltagerListe->removeNo(i);	// tar ut hvert enkelt objekt.
		if (temppeker->sjekkLand(ch)) {						// sammenligner dataene.
			temppeker->display();						// og displayer hvis dataene er like med det brukeren skrev inn.
		}
		deltagerListe->add(temppeker);		// legger objektet tilbake igjen.
	}
}

void Deltagere::MenyD()
{	
	char valg;                //  Brukerens valg.
	skrivMenyD();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': lagNyDeltager();; break;
		case 'E': endreDeltager();  break;
		case 'A': skrivUt();  break;
		case 'S': skrivUtValgt();  break;
		default:  skrivMenyD();       break;
		}
		valg = les();
	}
}

void Deltagere::skrivMenyD() // skriver ut valgene på skjermen.
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny deltaker";
	cout << "\n\tE = Endre en deltaker";
	cout << "\n\tA = Skriv alle data om alle deltakere";
	cout << "\n\tS = Skriv alle data om en gitt deltaker";
	cout << "\n\tQ = Forrige meny";
}

void Deltagere::LesDeltagereFraFil()
{
	int temp;
	ifstream inn("gruppe03/DELTAGERE.DTA"); // åpner filen fra harddisk
	if (inn) // sjekker om fila finnes.
	{
		inn >> temp;
		while (!inn.eof() && deltagerListe->noOfElements() < MAXDELTAGERE) // sjekker om det en slutt på fil, eller lista er for stor.
		{
			Deltager* nyDeltager;	// så lages det et nytt deltagerobjekt
			nyDeltager = new Deltager(temp, inn);	// og legger det inn i lista
			deltagerListe->add(nyDeltager);		// baser på innskrevet nummer.
			sisteDeltager++;	// teller opp variabelen.
			inn >> temp;
		}
	}
	else
	{
		cout << "\nFil ikke funnet! " << endl;
	}
}

void Deltagere::skrivDeltagereTilFil()
{
	if (!deltagerListe->isEmpty())
	{
		ofstream ut("gruppe03/DELTAGERE.DTA");
		if (ut)
		{
			int temp = deltagerListe->noOfElements();
			for (int i = 1; i <= temp; i++)	// looper gjennom alle leger
			{
				Deltager* tempPeker = (Deltager*)deltagerListe->removeNo(i); // tar ut objekt
				tempPeker->skrivDeltagerTilFil(ut);	// kjorer funskjonen skriv
				deltagerListe->add(tempPeker);	// legger det inn i lista igjen.
			}
		}
		else
		{
			cout << "\nFil ikke tilgjengelig! " << endl;
		}
	}
}