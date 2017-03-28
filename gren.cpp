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
	//for (int i = 1; i <= antallOvelser; i++) // looper gjennom hele arrayen med ovelser
	//{
		//inn >> ovelser[i];	// leser inn ovelsenummeret
	//}
}

void Gren::SkrivGrenTilFil(ofstream & ut)
{
	ut << navn << '\n';	// skriver ut navn
	(typeResultat == poeng) ? ut << poeng << '\n' : ut << tid << '\n';	// skriver ut 0 eller 1 for poeng eller tid.
	ut << antallOvelser << '\n';
	//for (int i = 1; i <= antallOvelser; i++)	// looper hele ovelser arrayen.
	//{
		//ut << " " << ovelser[i];	// skriver ut ovelsenummer.
	//}
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

void Gren::displayValgt()
{
	display();
	for (int i = 1; i <= antallOvelser; i++)
	{
		ovelser[i]->skrivAlt();
	}
}


void Gren::MenyO()
{
	char tempNavn[MAXTXT];
	char valg;                //  Brukerens valg.
	skrivMenyO();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': nyOvelse(); break;
		case 'E': endreOvelse();  break;
		case 'F': cout << "\nFjerner en ævelse i: " << tempNavn;; break;
		case 'A': skrivAlle();  break;
		//case 'L': MenyOL(); break;
		//case 'R': MenyOR(); break;
		default:  skrivMenyO();       break;
		}
		valg = les();
	}
}
/*
void Gren::MenyOL()
{
int temp;
temp = les("\nSkriv inn nummer", MINDELTAGER, MAXDELTAGER);


// FIKS SENERE (SJEKKE NUMMER).



char valg;                //  Brukerens valg.
skrivMenyOL();                  //  skriver ut meny med valg.

valg = les();             //  Leser brukerens valg.
while (valg != 'Q') {
switch (valg) {
case 'S': cout << "\nSkriver deltagerliste om: " << temp; break;
case 'N': cout << "\nNy deltagerliste i øvelse: " << temp;  break;
case 'E': cout << "\nEndrer liste om " << temp; break;
case 'F': cout << "\nSletter deltagerliste i: " << temp;   break;
default:  skrivMenyOL();       break;
}
valg = les();
}
}

void Gren::MenyOR()
{
int temp;
temp = les("\nSkriv inn nummer", MINDELTAGER, MAXDELTAGER);


// FIKS SENERE (SJEKKE NUMMER).
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,



char valg;                //  Brukerens valg.
skrivMenyOR();                  //  skriver ut meny med valg.

valg = les();             //  Leser brukerens valg.
while (valg != 'Q') {
switch (valg) {
case 'S': cout << "\nSkriver resultatliste om: " << temp; break;
case 'N': cout << "\nNy deltagerliste i øvelse: " << temp;  break;
case 'F': cout << "\nSletter resultatliste i: " << temp;   break;
default:  skrivMenyOR();       break;
}
valg = les();
}
}*/

void Gren::skrivMenyO()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny øvelse";
	cout << "\n\tE = Endre en øvelse";
	cout << "\n\tA = Skriv alle data om alle øvelser";
	cout << "\n\tL = Startliste undermeny";
	cout << "\n\tR = Resultatliste undermeny";
	cout << "\n\tQ = Forrige meny";
}

void Gren::skrivMenyOL()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv deltakerliste";
	cout << "\n\tN = Ny deltakerliste";
	cout << "\n\tE = Endre deltakerliste";
	cout << "\n\tF = Fjerne deltakerliste";
	cout << "\n\tQ = Forrige meny";
}

void Gren::skrivMenyOR()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv resultatliste";
	cout << "\n\tE = Ny resultatliste";
	cout << "\n\tF = Fjerne resultatliste";
	cout << "\n\tQ = Forrige meny";
}

void Gren::returnNavn(char t[])
{
	strcpy(t, text);
}

void Gren::nyOvelse()
{
	if (antallOvelser < MAXOVELSER)
	{
		int tempID;
		tempID = les("\nLes inn unik ID", 1000, 9999);
		if(antallOvelser > 0)
		{
			for (int i = 1; i <= antallOvelser; i++)
			{
				if (!ovelser[i]->sjekkID(tempID))
				{
					char* temp;
					les("\n\tLes inn navn på ovelse", temp);
					if (!ovelser[i]->sjekkNavn(temp))
					{
						ovelser[++antallOvelser] = new Ovelse(tempID, temp);
					}
					else
					{
						cout << "\n\tNavn finnes allerede. " << endl;
					}
				}
				else
				{
					cout << "\n\tID finnes allerede." << endl;
				}
			}
		}
		else
		{
			char* temp;
			les("\n\tLes inn navn på ovelse", temp);
			ovelser[++antallOvelser] = new Ovelse(tempID, temp);
		}
	}
	else
	{
		cout << "\n\tOvelser er allerede fullt." << endl;
	}
}

void Gren::endreOvelse()
{
	if (antallOvelser > 0)
	{
		int tempID;
		tempID = les("\nLes inn ID på øvelse du vil endre", 1000, 9999);
		for (int i = 1; i <= antallOvelser; i++)
		{
			if (ovelser[i]->sjekkID(tempID))
			{
				ovelser[i]->endreOvelsen();
			}
			else
			{
				cout << "\n\tOvelsen med dette nummeret finnes ikke." << endl;
			}
		}
	}
	else
	{
		cout << "\n\tDet finnes ingen ovelser for øyeblikket" << endl;
	}
}

void Gren::skrivAlle()
{
	if (antallOvelser > 0) {
		for (int i = 1; i <= antallOvelser; i++)
		{
			ovelser[i]->skrivAlt();
		}
	}
	else
	{
		cout << "\n\tIngen ovelser. " << endl;
	}
}

void Gren::skrivOvelseTilFil(ofstream & ut)
{
	ut << antallOvelser << endl;
	for (int i = 1; i <= antallOvelser; i++)
	{
		ovelser[i]->skrivTilFil(ut);
	}
}

void Gren::lesOvelseFraFil(ifstream & inn)
{
	int temp, temp2;
	inn >> temp; 
	for (int i = 1; i <= temp; i++)
	{
		inn >> temp2; inn.ignore();
		ovelser[i] = new Ovelse(inn, temp2);
	}
}