#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h>

using namespace std;

#include "funksjoner.h"
#include "ovelse.h"
#include "enum.h"
#include "deltagere.h"

extern Deltagere deltagerobjekt;

void Ovelse::flyttStartliste(const int i, const int j)
{
	startListe[i][0] = startListe[j][0];
	startListe[i][1] = startListe[j][1];
}

void Ovelse::nyttDynamiskArray()
{
	int (*endretStartliste)[2] = new int[antallDeltagere + 1][2];

	for (int i = 1; i <= antallDeltagere; i++)
	{
		endretStartliste[i][0] = startListe[i][0];
		endretStartliste[i][1] = startListe[i][1];
	}
	delete[] startListe;
	startListe = endretStartliste;
	delete[] endretStartliste;
}

Ovelse::Ovelse(int i, char chr[]) : NumElement(i)
{
	ovelseNavn = new char[strlen(chr) + 1];
	strcpy(ovelseNavn, chr);	
	klokkeStart = lesKlokkeSlett();
	dato = lesDato();
	antallDeltagere = 0;
}

void Ovelse::endreOvelsen()
{
	cout << "\nHva vil du endre på? (N)avn, (D)ato eller (K)lokkeslett. Q for å avslutte " << endl;
	char ch = les();	// leser inn en uppercase tegn
	while (ch != 'Q')	// sjekker at brukeren ikke vil avslutte
	{
		switch (ch)		// Utfører brukerens valg
		{
		case 'N': endreNavn();					break; // sletter først navn, så leser inn nytt
		case 'D': endreOvelseDato();		    break; 
		case 'K': endreKlokkeslett();			break;
		default: break;
		}
		ch = les();
	}
}

void Ovelse::endreNavn()
{
	delete[] ovelseNavn; les("\n\tLes inn nytt navn", ovelseNavn);
}

void Ovelse::endreOvelseDato()
{
	dato = lesDato();
}

void Ovelse::endreKlokkeslett()
{
	klokkeStart = lesKlokkeSlett();
}

void Ovelse::skrivAlt()
{
	cout << "\n\tNummer: " << number 
		<< "\n\tNavn: " << ovelseNavn 
		<< "\n\tDato: " << dato 
		<< "\n\tKlokkeslett: " << klokkeStart 
		<< "\n\tAntall Deltagere: " << antallDeltagere << endl;
}

bool Ovelse::sjekkNavn(char c[])
{
	return(!strcmp(c, ovelseNavn));
}

bool Ovelse::sjekkID(int i)
{
	return(i == number);
}

void Ovelse::skrivStartliste()
{
	char temp[MAXTXT + 1] = "gruppe03/";
	char ch;
	filtype ft = startliste;

	lagFilNavn(temp, ft);

	ifstream inn(temp);
	if (inn)
	{
		inn >> ch >> antallDeltagere; inn.ignore();
		startListe = new int[antallDeltagere + 1][2];
		lesStartlisteFraFil(inn);
		for (int i = 1; i <= antallDeltagere; i++)
		{
			cout << "Startnummer: " << i << " ";
			deltagerobjekt.skrivID(startListe[i][1]);
		}
	}
	else
	{
		cout << "\n\tIngen startliste funnet." << endl;
	}
}

void Ovelse::nyStartliste()
{
	char temp[MAXTXT + 1] = "gruppe03/";
	int deltagerTemp;
	filtype ft = startliste;

	lagFilNavn(temp, ft);

	ifstream inn(temp);
	if (!inn)
	{
		antallDeltagere = les("Antall deltagere i denne øvelsen", MINDELTAGER, MAXDELTAGER);
		if (antallDeltagere <= deltagerobjekt.antallDeltagere())
		{
			startListe = new int[antallDeltagere + 1][2];
			for (int i = 1; i <= antallDeltagere; i++)
			{
				deltagerTemp = les("Deltagernummer", MINDELTAGERE, MAXDELTAGERE);
				if (deltagerobjekt.finnesID(deltagerTemp))
				{
					startListe[i][0] = i;
					startListe[i][1] = deltagerTemp;
					cout << "\n\tDeltager lagt til startlisten." << endl;
				}
				else
				{
					cout << "Ingen deltagere med dette nummeret." << endl;
					i--;
				}
			}
			skrivStartlisteTilFil();
		}
		else
		{
			cout << "\n\tIkke nok deltagere til å fylle en liste med så mange deltagere." << endl;
		}
	}
	else
	{
		cout << "\n\tStartliste finnes allerede." << endl;
	}

}

void Ovelse::endreStartliste()
{
	char valg;                //  Brukerens valg.
	skrivMenyOLE();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'S': minusStartlisteDeltager();	break;
		case 'N': plussStartlisteDeltager();				break;
		case 'F': 	break;
		default:  skrivMenyOLE();				break;
		}
		valg = les();
	}
}

void Ovelse::minusStartlisteDeltager()
{
	bool fantDeltager = false;
	int deltagerTemp, i = 1;
	deltagerTemp = les("\n\tDeltagernummeret du vil fjerne fra startlisten", MINDELTAGERE, MAXDELTAGERE);
	while(!fantDeltager || i <= antallDeltagere)
	{
		if (startListe[i][1] == deltagerTemp)
		{
			flyttStartliste(antallDeltagere, i);
			fantDeltager = true;
		}
		i++;
	}
	if (!fantDeltager)
	{
		cout << "\n\tFant ingen deltagere med dette nummeret" << endl;
	}
}

void plussStartlisteDeltager()
{

}

void Ovelse::skrivTilFil(ofstream &ut)
{
	ut << number << '\n' << ovelseNavn << '\n'
		<< klokkeStart << " " << dato << " " << antallDeltagere << endl;
}

Ovelse::Ovelse(ifstream & inn, int i) : NumElement (i)
{
	lesInnFraFil(ovelseNavn, inn);
	inn >> klokkeStart >> dato >> antallDeltagere; inn.ignore();
}

void Ovelse::lagFilNavn(char ch[], filtype ft)
{
	char temp[MAXTXT + 1] = "OV";
	char temp2[MAXTXT + 1];
	_itoa(number, temp2, 10);
	
	//char temp[MAXTXT + 1] = (ft == startliste) ?  ".STA" : ".RES";	// TIL SENERE INSPEKSJON, HJELP BLIR SATT PRIS PÅ *HINT HINT*

	if (ft == startliste)
	{
		char temp3[MAXTXT + 1] = ".STA";
		strcat(ch, temp);
		strcat(ch, temp2);
		strcat(ch, temp3);
	}
	else
	{ 
		char temp3[MAXTXT + 1] = ".RES"; 
		strcat(ch, temp);
		strcat(ch, temp2);
		strcat(ch, temp3);
	}
}

void Ovelse::MenyOR()
{
	char valg;                //  Brukerens valg.
	skrivMenyOR();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'S': skrivResultatListe();	break;
		case 'N': 			break;
		case 'E':  		break;
		case 'F':	break;
		default:  skrivMenyOR();       break;
		}
		valg = les();
	}
}

void Ovelse::skrivMenyOR()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS = Skriv resultatliste"
		<< "\n\tN = Ny resultatliste" 
		<< "\n\tF = Fjerne resultatliste"
		<< "\n\tQ = Forrige meny";
}

void Ovelse::skrivMenyOLE()
{
	cout << "\n\tFØLGENDE KOMMANDOER ER TILGJENGLIGE:"
		<< "\n\tN = Legge til ny deltager"
		<< "\n\tS = Slette en deltager"
		<< "\n\tB = Bytte en deltager med en annen"
		<< "\n\tQ = Forrige meny";
}

void Ovelse::lesStartlisteFraFil(ifstream & inn)
{
	for (int i = 1; i <= antallDeltagere; i++)
	{
		inn >> startListe[i][0] >> startListe[i][1];
		inn.ignore();
	}
}

void Ovelse::skrivStartlisteTilFil()
{
	filtype ft = startliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);

	ofstream ut(filnavn);
	ut << 'I ' << antallDeltagere << endl;
	for (int i = 1; i <= antallDeltagere; i++)
	{
		ut << startListe[i][0] << " " << startListe[i][1] << endl;
	}
}
