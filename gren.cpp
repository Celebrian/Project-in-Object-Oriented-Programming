#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>

using namespace std;

#include "gren.h"
#include "funksjoner.h"


Gren::Gren(char * ch) : TextElement(ch)
{
	navn = ch;
	char chr;  cout << "\nVelg resultat type: P(oeng)/T(id)";
	chr = les();
	typeResultat = (chr == 'P') ? poeng : tid;
	antallOvelser = 0;
}

Gren::Gren(char ch[], ifstream & inn) : TextElement(ch)
{
	navn = new char[strlen(ch) + 1]; // lager array med spesifik storrelse
	strcpy(navn, ch); // kopierer over i arrayen ch
	int temp; inn >> temp; inn.ignore(); // leser inn 0 eller 1 fra fil
	typeResultat = ((temp == 0) ? poeng : tid);	// hvor 0 = jente og 1 = gutt.
	inn >> antallOvelser; inn.ignore(); 
	for (int i = 1; i <= antallOvelser; i++) // looper gjennom hele arrayen med ovelser
	{
		inn >> ovelser[i];	// leser inn ovelsenummeret
	}
}

void Gren::SkrivGrenTilFil(ofstream & ut)
{
	ut << navn << '\n';	// skriver ut navn
	(typeResultat == poeng) ? ut << poeng << '\n' : ut << tid << '\n';	// skriver ut 0 eller 1 for poeng eller tid.
	ut << antallOvelser << '\n';
	for (int i = 1; i <= antallOvelser; i++)	// looper hele ovelser arrayen.
	{
		ut << " " << ovelser[i];	// skriver ut ovelsenummer.
	}
}

void Gren::endreNyGren()
{
	cout << "\nVil du endre på navnet? J(a) / N(ei) " << endl;
	char ch = les();
	if(ch != 'N')
	{
		delete[] navn;			// sletter det eksisterende navnet
		les("\n\tLes inn nytt navn", navn);	// leser det inn på nytt.
	}
}

void Gren::display()	// skriver ut data om gren til skjerm.
{
	cout << "\n\tNavn: " << navn
		<< "\n\tRegistrering av prestasjon: " <<
		((typeResultat == poeng) ? "poeng" : "tid")
		<< "\n\tAntall øvelser i gren: " << antallOvelser << endl;
}
