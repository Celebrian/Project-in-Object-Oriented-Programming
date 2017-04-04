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
	char chr; 
	skrivShit();
	chr = les();
	switch (chr){
	case 'T': typeResultat = tidel; break;
	case 'H': typeResultat = hundredel; break;
	case 'D': typeResultat = tusendel; break;
	case 'P': typeResultat = poengx; break;
	case 'X': typeResultat = poengxx; break;
	default: skrivShit(); break; 
	}
	antallOvelser = 0;
}

void Gren::skrivShit()
{
	cout << "\n\tT for tidel" 
		<< "\n\tH for hundredel" 
		<< "\n\tD for tusendel" 
		<< "\n\tP for poengX" 
		<< "\n\tX for poengXX" << endl;
}

Gren::Gren(char ch[], ifstream & inn) : TextElement(ch)
{
	navn = new char[strlen(ch) + 1]; // lager array med spesifik storrelse
	strcpy(navn, ch); // kopierer over i arrayen ch
	int temp; inn >> temp; inn.ignore(); // leser inn 0 eller 1 fra fil
	switch (temp) {
	case 0: typeResultat = tidel; break;
	case 1: typeResultat = hundredel; break;
	case 2: typeResultat = tusendel; break;
	case 3: typeResultat = poengx; break;
	case 4: typeResultat = poengxx; break;
	default: break; 
	}
	inn >> antallOvelser; inn.ignore(); 
	//for (int i = 1; i <= antallOvelser; i++) // looper gjennom hele arrayen med ovelser
	//{
		//inn >> ovelser[i];	// leser inn ovelsenummeret
	//}
}

void Gren::SkrivGrenTilFil(ofstream & ut)
{
	ut << navn << '\n';	// skriver ut navn
	switch (typeResultat) {
	case tidel: ut << tidel << '\n'; break;
	case hundredel: ut << hundredel << '\n'; break;
	case tusendel: ut << tusendel << '\n'; break;
	case poengx: ut << poengx << '\n'; break;
	case poengxx: ut << poengxx << '\n'; break;
	default: break; 
	}	// skriver ut 0 eller 1 for poeng eller tid.
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
		<< "\n\tRegistrering av prestasjon: ";
	switch (typeResultat) {
	case tidel: cout << "tidel" << '\n'; break;
	case hundredel: cout << "hundredel" << '\n'; break;
	case tusendel: cout << "tusendel" << '\n'; break;
	case poengx: cout << "poengx" << '\n'; break;
	case poengxx: cout << "poengxx" << '\n'; break;
	default: break;
	}
		cout << "\n\tAntall øvelser i gren: " << antallOvelser << endl;
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
		case 'R': resultatListeMeny(); break;
		default:  skrivMenyO();       break;
		}
		valg = les();
	}
}

void Gren::MenyOL()
{
	int temp;
	char valg;                //  Brukerens valg.

	temp = les("\nSkriv inn Øvelsenummer", 1000, 9999);
	for (int i = 1; i <= antallOvelser; i++)
	{
		if (ovelser[i]->sjekkID(temp))
		{
			skrivMenyOL();                  //  skriver ut meny med valg.
	
			valg = les();             //  Leser brukerens valg.
			while (valg != 'Q') {
				switch (valg) {
				case 'S': ovelser[i]->skrivDeltagerListe(temp);					break;
				case 'N': cout << "\n\tNy deltagerliste";					break;
				case 'E': cout << "\n\tEndre deltagerliste";				break;
				case 'F': cout << "\n\tFjern deltagerliste";				break;
				default:  skrivMenyOL();									break;
				}
				valg = les();
			}
		}
		else
		{
			cout << "\n\tIngen øvelser med denne ID" << endl;
		}
	}
}

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

void Gren::returnNavn(char t[])
{
	strcpy(t, text);
}

void Gren::nyOvelse()
{
	bool idfinnesikke = true;
	bool navnfinnesikke = true;
	if (antallOvelser < MAXOVELSER)
	{
		int tempID;
		tempID = les("\nLes inn unik ID", MINOVNR, MAXOVNR);
		if(antallOvelser > 0)
		{
			for (int i = 1; i <= antallOvelser; i++)
			{
				if (ovelser[i]->sjekkID(tempID))
				{
					idfinnesikke = false;
				}
			}
			if (idfinnesikke) 
			{
				char* temp;
				les("\n\tLes inn navn på ovelse", temp);
				for (int j = 1; j <= antallOvelser; j++)
				{
					if (ovelser[j]->sjekkNavn(temp)) 
					{
						navnfinnesikke = false;
					}				
				}
				if (navnfinnesikke)
				{
					ovelser[++antallOvelser] = new Ovelse(tempID, temp, typeResultat);
				}
				else
				{
					cout << "\n\tNavn finnes allerede. " << endl;
				}
			}
			else
			{
				cout << "\n\tID finnes alerede." << endl;
			}
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
		tempID = les("\nLes inn ID på øvelse du vil endre", MINOVNR, MAXOVNR);
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
		ovelser[i] = new Ovelse(inn, temp2,typeResultat);
	}
}

void Gren::resultatListeMeny()
{
	int temp;
	temp = les("\nSkriv inn nummer", MINDELTAGER, MAXDELTAGER);
	for (int i = 1; i <= antallOvelser; i++)
	{
		if (ovelser[i]->sjekkID(temp)) 
		{
			ovelser[i]->MenyOR(temp);
		}
		else
		{
			cout << "\n\tØvelsen finnes ikke!" << endl;
		}
	}
}
