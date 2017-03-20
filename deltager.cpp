#include <iostream>

using namespace std;

#include "deltager.h"
#include "funksjoner.h"
#include "const.h"
#include "enum.h"

Deltager::Deltager(int n) : NumElement(n)
{
	les("\nSkriv inn navn: ", navn); // leser inn navn.
	lesNasjon("\nSkriv inn nasjonsforkortelse", nasjon, LANDSKODE);	// leser inn en forkortelse på tre upper-case bokstaver
	char ch;  cout << "\nVelg kjønn G(utt)/J(ente)";	// Setter kjønn i enumen
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
	cout << "\nHva vil du endre på? (N)avn, n(A)sjon eller (K)jonn. Q for å avslutte " << endl;
	char ch = les();	// leser inn en uppercase tegn
	while (ch != 'Q');	// sjekker at brukeren ikke vil avslutte
	{
		switch (ch)		// Utfører brukerens valg
		{
		case 'N': delete[] navn; les("\nLes inn nytt navn", navn); break; // sletter først navn, så leser inn nytt
		case 'A': les("\nLes inn ny nasjon", nasjon, MAXNASJONER); break; // leser inn en ny gyldig nasjon
		case 'K': char chr;  cout << "\nVelg kjønn G(utt)/J(ente)"; // bestemmer kjønn på nyt
			chr = les();
			gender = (ch == 'M') ? gutt : jente; break;
		default: break;
		}
	}
}

void Deltager::display()	// skriver ut valgte data om objektet
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn << "\n\tKjønn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}

void Deltager::displayAll()	// leser ut alle data om objektet
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn
		<< "\n\tNasjon: " << nasjon << "\n\tKjønn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}

bool Deltager::sjekkLand(char ch[LANDSKODE])	// sjekker at en nasjon faktisk eksisterer.
{
	return(nasjon == ch);
}

void Deltager::skrivDeltagerTilFil(ofstream & ut) // skriver data fra objektet til fil.
{
	ut << number << '\n'; 
	ut << navn << '\n';
	ut << nasjon << '\n';
	(gender == jente) ? ut << jente : ut << gutt << '\n';
}
