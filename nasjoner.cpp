#include <iostream>

using namespace std;

#include "ListTool2B.h"
#include "funksjoner.h"
#include "deltagere.h"
#include "nasjoner.h"
#include "nasjon.h"

extern Deltagere deltagerobjekt;


Nasjoner::Nasjoner()
{
	nasjonListe = new List(Sorted);							//Setter nasjonListe til å peke på en ny sorted list
}
void Nasjoner::skrivMenyN()									//Skriv undermenyen for N til skjerm
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
	char valg;						//  Brukerens valg.
	skrivMenyN();                  //  skriver ut meny med valg.

	valg = les();				  //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': registrerNasjon();			break;
		case 'E': endreNasjon();				break;
		case 'A': skrivAlleNasjoner();			break;
		case 'T': skrivNasjonDeltagere();		break;
		case 'S': skrivEnNasjon();				break;
		default:  skrivMenyN();					break;
		}
		valg = les();
	}
}

void Nasjoner::registrerNasjon()
{
	Nasjon* nyNasjon;
	char temp[LANDSKODE + 1];

	if (nasjonListe->noOfElements() < MAXNASJONER)				//Hvis det er plass til flere nasjoner
	{
		lesNasjon("Landkode på formen XXX", temp, LANDSKODE);	//Les inn landskode
		if (!nasjonListe->inList(temp))							//Hvis landskoden IKKE finnes fra før
		{
			nyNasjon = new Nasjon(temp);						//Lager nytt objekt
			nasjonListe->add(nyNasjon);							//og legger inn i lista
			cout << "\n\n\tNasjonen har blitt lagt til." << endl;
		}
		else
		{
			cout << "\n\tDet finnes allerede en nasjon med dette navnet." << endl;
		}
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

	if (!nasjonListe->isEmpty())								//Skjekker at det finnes minst en nasjon
	{
		lesNasjon("Skriv inn landskode på nasjon du vil endre på", temp, LANDSKODE);
		if (nasjonListe->inList(temp))							//Hvis landskoden finnes i lista
		{
			tempNasjon = (Nasjon*)nasjonListe->remove(temp);	//Ta ut av lista
			tempNasjon->endreNasjon();							//Kjør objektets endre nasjon
			nasjonListe->add(tempNasjon);						//Og legg tilbake i lista
		}
		else
		{
			cout << "\n\tIngen nasjoner med denne landskoden!";
		}
	}
	else
	{
		cout << "\n\tDet finnes ingen nasjoner." << endl;
	}
}

void Nasjoner::skrivAlleNasjoner()
{
	if (!nasjonListe->isEmpty())									//Skjekker at det finnes minst en nasjon
	{
		nasjonListe->displayList();									//Kjører alle nasjoners display()
	}
	else
	{
		cout << "\n\tIngen nasjoner i lista." << endl;
	}
}

void Nasjoner::skrivNasjonDeltagere()
{
	char temp[LANDSKODE + 1];

	lesNasjon("Skriv inn landskode", temp, LANDSKODE);
	if (nasjonListe->inList(temp))							//Hvis landskoden finnes i lista
	{
		cout << "\n\tNasjon: " << temp << endl;				//Skriv landskoden
		deltagerobjekt.loopGjennom(temp);					//Og alle deltagere med denne landskoden
	}
	else
	{
		cout << "\n\tIngen nasjoner med denne landskoden." << endl;
	}
}

void Nasjoner::skrivEnNasjon()
{
	Nasjon* tempNasjon;
	char temp[LANDSKODE];

	if (nasjonListe->noOfElements() != 0)						//Skjekker at det finnes minst en nasjon
	{
		lesNasjon("Skriv inn landskode som det skal skrives informasjon om", temp, LANDSKODE);
		if (nasjonListe->inList(temp))							//Hvis den inleste nasjonen finnes
		{
			tempNasjon = (Nasjon*)nasjonListe->remove(temp);
			tempNasjon->displayAlt();									//Kjør denne nasjonens displayfunksjon
			nasjonListe->add(tempNasjon);
		}
		else
		{
			cout << "\n\tIngen nasjoner med denne landsforkortelsen." << endl;
		}
	}
	else
	{
		cout << "\n\tIngen nasjoner i lista." << endl;
	}
}

bool Nasjoner::finnesNasjon(const char t[])
{
	return (nasjonListe->inList(t));
}

void Nasjoner::plussDeltager(const char t[])
{
	Nasjon* nasjonptr;

	nasjonptr = (Nasjon*)nasjonListe->remove(t);
	nasjonptr->pluss();								//Teller opp antall deltagere i troppen
	nasjonListe->add(nasjonptr);
}

void Nasjoner::minusDeltager(const char t[])
{
	Nasjon* nasjonptr;

	nasjonptr = (Nasjon*)nasjonListe->remove(t);
	nasjonptr->minus();								//Teller ned antall deltagere i troppen
	nasjonListe->add(nasjonptr);
}

void Nasjoner::lesNasjonerFraFil()
{
	Nasjon* nyNasjon;
	char temp[LANDSKODE + 1];

	ifstream inn("gruppe03/NASJONER.DTA");
	if (inn)
	{
		inn.getline(temp, LANDSKODE);
		while (!inn.eof() && nasjonListe->noOfElements() < MAXNASJONER)
		{					//Leser så lenge fila ikke er slutt og det er plass til flere nasjoner
			nyNasjon = new Nasjon(inn, temp);
			nasjonListe->add(nyNasjon);
			nyNasjon = nullptr;

			inn.getline(temp, LANDSKODE);
		}
	}
	else
	{
		cout << "\n\n\tFant ikke filen Nasjoner.DTA" << endl;
	}
}

void Nasjoner::skrivNasjonerTilFil()
{
	if (!nasjonListe->isEmpty())							//Skriver ikke til fil hvis det ikke er noe å skrive
	{
		Nasjon* tempNasjon;
		ofstream ut("gruppe03/NASJONER.DTA");

		for (int i = 1; i <= nasjonListe->noOfElements(); i++)
		{
			tempNasjon = (Nasjon*)nasjonListe->removeNo(i);
			tempNasjon->skrivNasjonTilFil(ut);
			nasjonListe->add(tempNasjon);
		}
	}
}

