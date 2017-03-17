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
	antallDeltagere = les("Antall deltagere i troppen", MINDELTAGER, MAXDELTAGER);
	les("Skriv navnet på nasjonens kontaktperson", kontaktNavn);
	kontaktTelefon = lesTelefon();
}

void Nasjon::endreNasjon()
{
	char ch;

	cout << "\n\tHva vil du endre? "
		<< "\n\tN - Det fulle navnet til nasjonen."
		<< "\n\tK - Navn på kontaktperson"
		<< "\n\tT - Telefon på kontaktperson"
		<< "\n\tQ - Ingenting, gå opp en meny";
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
			<< "\n\tK - Navn på kontaktperson"
			<< "\n\tT - Telefon på kontaktperson"
			<< "\n\tQ - Ingenting, gå opp en meny";	break;
		}
		ch = les();
	}
}

void Nasjon::endreNasjonNavn()
{
	delete[] navn;
	les("Skriv inn nytt nasjonsnavn: ", navn);
}

void Nasjon::endreKontaktNavn()
{
	delete[] kontaktNavn;
	les("Skriv inn nytt navn på kontakt person: ", kontaktNavn);
}

void Nasjon::endreTelefon()
{
	kontaktTelefon = lesTelefon();
}

void Nasjon::display()
{
	cout << "\n\n\tLandskode: " << text
		<< "\n\tNasjonsnavn: " << navn
		<< "\n\tKontaktperson: " << kontaktNavn
		<< "\n\tTelefonkontakt: " << kontaktTelefon;
}

void Nasjon::displayAlt()
{
	cout << "\n\n\tLandskode: " << text
		<< "\n\tNasjonsnavn: " << navn
		<< "\n\tAntall deltagere: " << antallDeltagere
		<< "\n\tKontaktperson: " << kontaktNavn
		<< "\n\tTelefonkontakt: " << kontaktTelefon;
}

