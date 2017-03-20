#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>

using namespace std;

#include "const.h"
#include "funksjoner.h"
#include "nasjon.h"

Nasjon::Nasjon(char * landskode) : TextElement(landskode)
{
	les("Komplett nasjonsnavn", navn);
	antallDeltagere = les("Antall deltagere i troppen", MINDELTAGERE, MAXDELTAGERE);
	les("Skriv navnet p� nasjonens kontaktperson", kontaktNavn);
	kontaktTelefon = lesTelefon();
}

Nasjon::Nasjon(ifstream & inn, char* landskode) : TextElement(landskode)
{
	lesInnFraFil(navn, inn);
	inn >> antallDeltagere; inn.ignore();
	lesInnFraFil(kontaktNavn, inn);
	inn >> kontaktTelefon; inn.ignore();
}

void Nasjon::endreNasjon()
{
	char ch;

	cout << "\n\tHva vil du endre? "
		<< "\n\tN - Det fulle navnet til nasjonen."
		<< "\n\tK - Navn p� kontaktperson"
		<< "\n\tT - Telefon p� kontaktperson"
		<< "\n\tQ - Ingenting, g� opp en meny";
	ch = les();
	while (ch != 'Q')
	{
		switch (ch)
		{
		case 'N': endreNasjonNavn();	break;
		case 'K': endreKontaktNavn();	break;
		case 'T': endreTelefon();		break;
		default: cout << "\n\tHva vil du endre? "
			<< "\n\tN - Det fulle navnet til nasjonen."
			<< "\n\tK - Navn p� kontaktperson"
			<< "\n\tT - Telefon p� kontaktperson"
			<< "\n\tQ - Ingenting, g� opp en meny";	break;
		}
		ch = les();
	}
}

void Nasjon::endreNasjonNavn()
{
	delete[] navn;									//Frigj�r navn array i minnet
	les("Skriv inn nytt nasjonsnavn: ", navn);		//Leser inn nytt navn
	cout << "\n\tNasjonsnavn endret." << endl;
}

void Nasjon::endreKontaktNavn()
{
	delete[] kontaktNavn;							//Frigj�r kontaktnavn i minnet
	les("Skriv inn nytt navn p� kontakt person: ", kontaktNavn);
	cout << "\n\tNavnet p� kontaktperson endret." << endl;
}

void Nasjon::endreTelefon()
{
	kontaktTelefon = lesTelefon();
	cout << "\n\tTelefonnummer til kontaktperson endret." << endl;
}

void Nasjon::display()
{
	cout << "\n\tLandskode: " << text
		<< "\n\tNasjonsnavn: " << navn
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
		<< "\n\tTelefonkontakt: " << kontaktTelefon;
}

void Nasjon::skrivNasjonTilFil(ofstream & ut)
{
	ut << text << endl
		<< navn << endl
		<< antallDeltagere << endl
		<< kontaktNavn << endl
		<< kontaktTelefon << endl;
}

