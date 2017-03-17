#include <iostream>

using namespace std;

#include "gren.h"
#include "funksjoner.h"


Gren::Gren(char * ch) : TextElement(ch)
{
	navn = ch;
	char chr;  cout << "\nVelg resultat type: P(oeng)/T(id)";
	chr = les();
	typeResultat = (chr == 'P') ? poeng : tid;
}

void Gren::endreNyGren()
{
	cout << "\nVil du endre på navnet? J(a) / N(ei) " << endl;
	char ch = les();
	while (ch != 'N');
	{
		delete[] navn;
		les("\n\tLes inn nytt navn", navn);
	}
}

void Gren::display()
{
	cout << "\n\tNavn: " << navn
		<< "\n\tRegistrering av prestasjon: " <<
		((typeResultat == poeng) ? "poeng" : "tid")
		<< "\n\tAntall øvelser i gren: " << antallOvelser << endl;
}
