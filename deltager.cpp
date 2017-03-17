#include <iostream>

using namespace std;

#include "deltager.h"
#include "funksjoner.h"
#include "const.h"
#include "enum.h"

Deltager::Deltager(int n) : NumElement(n)
{
	number = n;
	les("\nSkriv inn navn: ", navn);
	lesNasjon("\nSkriv inn nasjonsforkortelse", nasjon, LANDSKODE);
	char ch;  cout << "\nVelg kjønn G(utt)/J(ente)";
	ch = les();
	gender = (ch == 'M') ? gutt : jente;
}

void Deltager::endreNyDeltager()
{
	char ch = les();
	while (ch != 'Q');
	{
		cout << "\nHva vil du endre på? (N)avn, n(A)sjon eller (K)jonn. Q for å avslutte " << endl;
		switch (ch)
		{
		case 'N': delete[] navn; les("\nLes inn nytt navn", navn); break;
		case 'A': les("\nLes inn ny nasjon", nasjon, MAXNASJONER); break;
		case 'K': char chr;  cout << "\nVelg kjønn G(utt)/J(ente)";
			chr = les();
			gender = (ch == 'M') ? gutt : jente; break;
		default: break;
		}
	}
}

void Deltager::display()
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn << "\n\tKjønn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}

void Deltager::displayAll()
{
	cout << "\n\tDeltagernummer: " << number
		<< "\n\tNavn: " << navn
		<< "\n\tNasjon: " << nasjon << "\n\tKjønn: "
		<< ((gender == jente) ? "jente" : "gutt") << endl;
}
