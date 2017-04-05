#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>

using namespace std;

#include "const.h"
#include "funksjoner.h"
#include "nasjon.h"

Nasjon::Nasjon(char * landskode) : TextElement(landskode)	//Sender landskode opp til text
{
	les("Komplett nasjonsnavn", navn);
	les("Skriv navnet p� nasjonens kontaktperson", kontaktNavn);
	kontaktTelefon = lesTelefon();
	les("Annen informasjon", annet);
	antallDeltagere = 0;
}

Nasjon::Nasjon(ifstream & inn, char* landskode) : TextElement(landskode)	//Sender landskode med til text
{
	lesInnFraFil(navn, inn);
	lesInnFraFil(kontaktNavn, inn);
	inn >> kontaktTelefon; inn.ignore();
	lesInnFraFil(annet, inn);
	antallDeltagere = 0;
}

void Nasjon::skrivMenyNE()
{
	cout << "\n\tHva vil du endre? "
		<< "\n\tN - Det fulle navnet til nasjonen."
		<< "\n\tK - Navn p� kontaktperson"
		<< "\n\tT - Telefon p� kontaktperson"
		<< "\n\tA - Annen informasjon"
		<< "\n\tQ - Ingenting, g� opp en meny";
}

void Nasjon::endreNasjon()
{
	skrivMenyNE();
	char ch = les();
	while (ch != 'Q')
	{
		switch (ch)
		{
		case 'N': endreNasjonNavn();	break;
		case 'K': endreKontaktNavn();	break;
		case 'T': endreTelefon();		break;
		case 'A': endreAnnet();			break;
		default:						break;
		}
		skrivMenyNE();
		ch = les();
	}
}

void Nasjon::endreNasjonNavn()
{
	delete[] navn;									//Frigj�r navn array i minnet
	les("Skriv inn nytt nasjonsnavn: ", navn);		//Leser inn nytt navn
	cout << "\n\tNasjonsnavn endret." << endl << endl;
}

void Nasjon::endreKontaktNavn()
{
	delete[] kontaktNavn;							//Frigj�r kontaktnavn i minnet
	les("Skriv inn nytt navn p� kontakt person: ", kontaktNavn);
	cout << "\n\tNavnet p� kontaktperson endret." << endl << endl;
}

void Nasjon::endreTelefon()
{
	kontaktTelefon = lesTelefon();
	cout << "\n\tTelefonnummer til kontaktperson endret." << endl << endl;
}

void Nasjon::endreAnnet()
{
	delete[] annet;
	les("Skriv inn annen informasjon", annet);
	cout << "\n\tAnnen informasjon endret." << endl << endl;
}

void Nasjon::display()
{
	cout << "\n\tLandskode: " << text
		<< "\n\tNasjonsnavn: " << navn
		<< "\n\tAntall deltagere i troppen: " << antallDeltagere
		<< "\n\tKontaktperson: " << kontaktNavn
		<< "\n\tTelefonkontakt: " << kontaktTelefon
		<< endl << endl;
}

void Nasjon::displayAlt()
{
	cout << "\n\n\tLandskode: " << text
		<< "\n\tNasjonsnavn: " << navn
		<< "\n\tAntall deltagere: " << antallDeltagere
		<< "\n\tKontaktperson: " << kontaktNavn
		<< "\n\tTelefonkontakt: " << kontaktTelefon
		<< "\n\tAnnen informasjon: " << annet
		<< endl << endl;
}

void Nasjon::plussDeltager()
{
	antallDeltagere++;
}

void Nasjon::minusDeltager()
{
	antallDeltagere--;
}

void Nasjon::skrivNasjonTilFil(ofstream & ut)
{
	ut << text << endl
		<< navn << endl
		<< kontaktNavn << endl
		<< kontaktTelefon << endl
		<< annet << endl;
}

