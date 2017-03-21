#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>

using namespace std;

#include "deltager.h"
#include "funksjoner.h"
#include "const.h"
#include "enum.h"
#include "nasjoner.h"
#include "nasjon.h"

extern Nasjoner nasjonerObjekt;

Deltager::Deltager(int n, char chr[]) : NumElement(n)
{
	strcpy(nasjon, chr);
	les("\nSkriv inn navn: ", navn); // leser inn navn.
	char ch;  cout << "\nVelg kj�nn G(utt)/J(ente)";	// Setter kj�nn i enumen
	ch = les();
	gender = (ch == 'G') ? gutt : jente;
}

Deltager::Deltager(int n, ifstream & inn) : NumElement(n)
{
	lesInnFraFil(navn, inn); // leser in navn.
	inn.getline(nasjon, LANDSKODE); // leser inn nasjonforkortelse.
	int temp;
	inn >> temp; inn.ignore();		// leser inn 0 eller 1 fra fil
	gender = ((temp == 0) ? jente : gutt);	// hvor 0 = jente og 1 = gutt.
}

void Deltager::endreNyDeltager()
{
	cout << "\nHva vil du endre p�? (N)avn, n(A)sjon eller (K)jonn. Q for � avslutte " << endl;
	char ch = les();	// leser inn en uppercase tegn
	while (ch != 'Q')	// sjekker at brukeren ikke vil avslutte
	{
		switch (ch)		// Utf�rer brukerens valg
		{
		case 'N': endreNavn();					break; // sletter f�rst navn, s� leser inn nytt
		case 'A': endreDeltagersNasjon(nasjon); break; // leser inn en ny gyldig nasjon
		case 'K': endreKjonn();					break;
		default: break;
		}
		ch = les();
	}
}

void Deltager::display()	// skriver ut valgte data om objektet
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn << "\n\tKj�nn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}

void Deltager::displayAll()	// leser ut alle data om objektet
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn
		<< "\n\tNasjon: " << nasjon << "\n\tKj�nn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}

bool Deltager::sjekkLand(char ch[LANDSKODE])	// sjekker at en nasjon faktisk eksisterer.
{
	return(!strcmp(nasjon, ch)); // sjekker om de er like og returnerer !0 hvis de er.
}

void Deltager::skrivDeltagerTilFil(ofstream & ut) // skriver data fra objektet til fil.
{
	ut << number << '\n'; 
	ut << navn << '\n';
	ut << nasjon << '\n';
	(gender == jente) ? ut << jente << '\n' : ut << gutt << '\n';
}

void Deltager::lesInnNasjon(char ch[])
{
	char temp[LANDSKODE];
	lesNasjon("\nLess inn nasjonsforkortelse ", temp, LANDSKODE);
	if (nasjonerObjekt.finnesNasjon(temp)) {
		strcpy(ch, temp);
		cout << ch << endl;
		// leser inn en nasjonsforkortelse p� 3 bokstaver, sjekker om den finnes i nasjoner lista
		// og returnerer det som en array.
	}
	else 
	{
		cout << "\n\tNasjonen finnes ikke! " << endl;
	}
}

void Deltager::endreDeltagersNasjon(char ch[])
{
	char gammel[LANDSKODE]; // tar vare p� den gamle nasjonsforkortelsen
	strcpy(gammel, ch);	// ved � kopiere den inn i en temp array.
	char temp[LANDSKODE];
	lesNasjon("\nLess inn nasjonsforkortelse ", temp, LANDSKODE);
	if (nasjonerObjekt.finnesNasjon(temp)) {
		strcpy(ch, temp); // lager en ny temp array hvor det leses inn en ny nasjonsforkortelse
						  // som m� finnes i nasjoner lista for � bli kopiert over i nasjon arrayen.
		nasjonerObjekt.minusDeltager(gammel);	// teller ned antall deltagere i den nasjonen som deltager ble flyttet fra.
		nasjonerObjekt.plussDeltager(temp);		// teller opp antall deltagere i den nasjonen deltageren ble flytta til.
	}
	else
	{
		cout << "\n\tNasjonen finnes ikke! " << endl;
	}
}

void Deltager::endreNavn()
{
	delete[] navn; les("\nLes inn nytt navn", navn);
	// sletter f�rst navnet, ogs� leser inn nytt navn.
}

void Deltager::endreKjonn()
{
	char chr;  cout << "\nVelg kj�nn G(utt)/J(ente)";	// bestemmer kj�nn p� nytt
	chr = les();
	gender = (chr == 'M') ? gutt : jente; 
}