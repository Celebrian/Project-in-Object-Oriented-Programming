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
	antallDeltagere = les("Antall deltagere i troppen", MINDELTAGER, MAXDELTAGER);
	les("Skriv navnet på nasjonens kontaktperson", kontaktNavn);
	kontaktTelefon = lesTelefon();
}

void Nasjon::endreNasjon()
{
	char ch;

	cout << "\n\tHva vil du endre? "
		<< "\n\tN - Det fulle navnet til nasjonen."
		<< "\n\tK - Endre navn på kontaktperson"
		<< "\n\tT - Endre telefon på kontaktperson"
		<< "\n\tQ - For å gå tilbake";
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
			<< "\n\tK - Endre navn på kontaktperson"
			<< "\n\tT - Endre telefon på kontaktperson"
			<< "\n\tQ - For å gå tilbake";	break;
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

