#include <iostream>

using namespace std;

#include "grener.h"
#include "funksjoner.h"
#include "const.h"
#include "gren.h"

Grener::Grener() // lager en ny liste med gren objekter
{
	grenListe = new List(Sorted);
}

void Grener::lagNyGren()
{
	Gren* grenptr;
	bool fantNavn = false;
	char* temp;
	char tmpnavn[MAXTXT + 1];
	les("\n\tSkriv inn navn på gren", temp);

	for (int i = 1; i <= grenListe->noOfElements(); i++)	//Går gjennom eksisterende grener
	{
		grenptr = (Gren*)grenListe->removeNo(i);
		grenptr->returnNavn(tmpnavn);						//Henter navnet på grenen
		if (erLik(temp, tmpnavn))							//Sammenlikner navn, om de er like
		{
			fantNavn = true;								//Setter at det ble funnet navn
		}
		grenListe->add(grenptr);
	}
	if (!fantNavn)  // sjekker om grenene allerede finnes
	{
			grenptr = new Gren(temp); // lager en ny gren med navnet
			grenListe->add(grenptr); // og legger den til i lista.
	}
	else
	{
		cout << "\n\tGrenen finnes allerede!" << endl;
	}
}

void Grener::endreGren()
{
	Gren* temppeker;
	bool fantNavn = false;
	char* temp;
	char tmpnavn[MAXTXT + 1];

	if (!grenListe->isEmpty())
	{
		les("\n\tSkriv inn navn på gren", temp);

		for (int i = 1; i <= grenListe->noOfElements(); i++)	//Går gjennom eksisterende grener
		{
			temppeker = (Gren*)grenListe->removeNo(i);
			temppeker->returnNavn(tmpnavn);						//Henter navnet på grenen
			if (erLik(temp, tmpnavn))							//Sammenlikner navn, om de er like
			{
				fantNavn = true;								//Setter at det ble funnet navn
			}
			grenListe->add(temppeker);
		}

		if (fantNavn)
		{
			temppeker = (Gren*)grenListe->remove(tmpnavn); // tar den ut av lista
			temppeker->endreNyGren();					// kjører endre funkjson
			grenListe->add(temppeker);					// og legger den inn igjen.
		}
		else
		{
			cout << "\n\tFant ingen grener med dette navnet." << endl;
		}
	}
	else
	{
		cout << "\n\tDet finnes ingen grener i lista!" << endl;
	}
}

void Grener::skrivUt() // skriver ut data om alle objekter i lista
{
	grenListe->displayList();
}

void Grener::skrivUtValgt()
{
	Gren* temppeker;
	char* temp; // leser inn navn på gren du vil se data om.
	bool fantNavn = false;
	char tmpnavn[MAXTXT + 1];
	les("\nSkriv inn navn på gren: ", temp);

	for (int i = 1; i <= grenListe->noOfElements(); i++)	//Går gjennom eksisterende grener
	{
		temppeker = (Gren*)grenListe->removeNo(i);
		temppeker->returnNavn(tmpnavn);						//Henter navnet på grenen
		if (erLik(temp, tmpnavn))							//Sammenlikner navn, om de er like
		{
			fantNavn = true;								//Setter at det ble funnet navn
		}
		grenListe->add(temppeker);
	}
	if (fantNavn)	// sjekker om grenen finnes.
	{
		temppeker = (Gren*)grenListe->remove(tmpnavn);
		temppeker->displayValgt();
		grenListe->add(temppeker);
		// tar gren ut av lista, displayer den, og setter den inn igjen.
	}
	else {
		cout << "\n\tGren finnes ikke." << endl;
	}
}

void Grener::MenyG()
{
	
		char valg;                //  Brukerens valg.
		skrivMenyG();                  //  skriver ut meny med valg.

		valg = les();             //  Leser brukerens valg.
		while (valg != 'Q') {
			switch (valg) {
			case 'N': lagNyGren();			break;
			case 'E': endreGren();			break;
			case 'A': skrivUt();			break;
			case 'S': skrivUtValgt();		break;
			default:						break;
			}
			SkrivGrenerTilFil();
			skrivMenyG();
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

void Grener::finnGren()				// sjekker om en gren finner, før man får øvelse meny.
{
	if (!grenListe->isEmpty())	// sjekker om grenlista faktisk inneholder elementer.
	{
		Gren* temppeker;
		char* temp; // leser inn navn på gren du vil se data om.
		bool fantNavn = false;
		char tmpnavn[MAXTXT + 1];

		les("\nSkriv inn navn på gren: ", temp);

		for (int i = 1; i <= grenListe->noOfElements(); i++)	//Går gjennom eksisterende grener
		{
			temppeker = (Gren*)grenListe->removeNo(i);
			temppeker->returnNavn(tmpnavn);						//Henter navnet på grenen
			if (erLik(temp, tmpnavn))							//Sammenlikner navn, om de er like
			{
				fantNavn = true;								//Setter at det ble funnet navn
			}
			grenListe->add(temppeker); // legger den tilbake i lista.
		}
		if (fantNavn)	// kjøres hvis de to navnene er like. aka innskrevet er lik navnet til objektet.
		{
			temppeker->MenyO();	//kjører menyen til øvelse objektet.
		}
		else
		{
			cout << "\n\tFant ingen gren med dette navn." << endl;
		}
	}
	else
	{
		cout << "\n\tDet finnes ingen grener." << endl;
	}
}

void Grener::LesGrenerFraFil()
{
	char temp[MAXTXT+1];
	ifstream inn("gruppe03/GRENER.DTA"); // åpner filen fra harddisk
	if (inn) // sjekker om fila finnes.
	{
		inn.getline(temp, MAXTXT);
		while (!inn.eof()) // sjekker om det en slutt på fil, eller lista er for stor.
		{
			Gren* nyGren;	// så lages det et nytt deltagerobjekt
			nyGren = new Gren(temp, inn);	// og legger det inn i lista
			grenListe->add(nyGren);		// baser på innskrevet nummer.
			inn.getline(temp, MAXTXT);
		}
	}
	else
	{
		cout << "\nFil ikke funnet! " << endl;
	}
}

void Grener::SkrivGrenerTilFil()
{
	if (!grenListe->isEmpty()) // sjekker om lista er tom.
	{
		ofstream ut("gruppe03/GRENER.DTA"); // åpner fil
		if (ut)
		{
			int temp = grenListe->noOfElements();  // henter antall i lista
			for (int i = 1; i <= temp; i++)	// looper gjennom alle grener
			{
				Gren* grenPeker = (Gren*)grenListe->removeNo(i); // tar ut objekt
				grenPeker->SkrivGrenTilFil(ut);	// kjorer funskjonen skriv
				grenListe->add(grenPeker);	// legger det inn i lista igjen.
			}
		}
		else
		{
			cout << "\nFil ikke tilgjengelig! " << endl;
		}
	}
}

void Grener::skrivOvelserTilFil()
{
	if (!grenListe->isEmpty()) 
	{
		ofstream utfil("gruppe03/OVELSER.DTA");
		if (utfil) 
		{
			int temp = grenListe->noOfElements();  // henter antall i lista
			for (int i = 1; i <= temp; i++)	// looper gjennom alle grener
			{
				Gren* grenPeker = (Gren*)grenListe->removeNo(i); // tar ut objekt
				utfil << i << endl;
				grenPeker->skrivOvelseTilFil(utfil);	// kjorer funskjonen skriv
				grenListe->add(grenPeker);	// legger det inn i lista igjen.
			}
		}

	}
}

void Grener::lesOvelserFraFil()
{
	int temp;
	ifstream innfil("gruppe03/OVELSER.DTA"); // åpner filen fra harddisk
	if (innfil) // sjekker om fila finnes.
	{
		innfil >> temp; innfil.ignore();
		while (!innfil.eof()) // sjekker om det en slutt på fil, eller lista er for stor.
		{
			Gren* grenPeker = (Gren*)grenListe->removeNo(temp); // tar ut objekt
			grenPeker->lesOvelseFraFil(innfil);	// kjorer funskjonen les
			grenListe->add(grenPeker);	// legger det inn i lista igjen.
		}
	}
	else
	{
		cout << "\nFil ikke funnet! " << endl;
	}
}
