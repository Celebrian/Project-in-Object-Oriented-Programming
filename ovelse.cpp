#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

#include "funksjoner.h"
#include "ovelse.h"
#include "enum.h"
#include "deltagere.h"
#include "poeng.h"
#include "const.h"
#include "medaljer.h"

extern Deltagere deltagerobjekt;
extern Poeng poengobjekt;
extern Medaljer medaljeObjekt;

Ovelse::Ovelse(int i, char chr[], resultatType rt) : NumElement(i)
{
	ovelseNavn = new char[strlen(chr) + 1];
	strcpy(ovelseNavn, chr);	
	klokkeStart = lesKlokkeSlett();
	dato = lesDato();
	antallDeltagere = 0;
	resultatMetode = rt;
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

void Ovelse::skrivDeltagerListe(const int id)
{

}

void Ovelse::skrivTilFil(ofstream &ut)
{
	ut << number << '\n' << ovelseNavn << '\n'
		<< klokkeStart << " " << dato << " " << antallDeltagere << endl;
}

Ovelse::Ovelse(ifstream & inn, int i, resultatType rs) : NumElement (i)
{
	lesInnFraFil(ovelseNavn, inn);
	inn >> klokkeStart >> dato >> antallDeltagere; inn.ignore();
	resultatMetode = rs;
}

void Ovelse::lagFilNavn(int id, char ch[], filtype ft)
{
	char temp[MAXTXT + 1] = "OV";
	char temp2[MAXTXT + 1];
	_itoa(id, temp2, 10);
	
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

void Ovelse::MenyOR(int id)
{
	char valg;                //  Brukerens valg.
	skrivMenyOR();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'S': skrivResultatListe(id); break;
		case 'N': nyResultatliste(id);  break;
		case 'F': cout << "\nSletter resultatliste i: ";  break;
		default:  skrivMenyOR();       break;
		}
		valg = les();
	}
}

void Ovelse::skrivMenyOR()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv resultatliste";
	cout << "\n\tN = Ny resultatliste";
	cout << "\n\tF = Fjerne resultatliste";
	cout << "\n\tQ = Forrige meny";
}

void Ovelse::skrivResultatListe(int id)
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(id, filnavn, ft);
	
	ifstream inn(filnavn);
	if (inn)
	{
		char* temp;
		lesInnFraFil(temp, inn);
		cout << temp;
	}
	else
	{
		cout << "\n\tResultatliste finnes ikke." << endl;
	}
}

void Ovelse::nyResultatliste(int id)
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(id, filnavn, ft);
	
	ifstream inn(filnavn);
	if (!inn)
	{
		inn.close();
		filtype ft = startliste;
		char filnavn2[MAXTXT + 1] = "gruppe03/";
		lagFilNavn(id, filnavn, ft);
		ifstream innfil(filnavn2);
		if (innfil)
		{
			char sortertemp;
			innfil >> sortertemp;
			innfil >> antallDeltagere;
			resultatListe = new float[antallDeltagere + 1][3];
			lagResultat(innfil);
		}
		else
		{
			cout << "\n\tFinner ikke startliste." << endl;
		}
	}
	else
	{
		cout << "\n\tResultatliste finnes allerede. " << endl;
		inn.close();
	}
}

void Ovelse::lagResultat(ifstream & inn)
{
	for (int i = 1; i < antallDeltagere; i++)
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1];
		inn.ignore();

		cout << "\n\tStartnummer: " << resultatListe[i][0];
		deltagerobjekt.skrivDeltagerStart(resultatListe[i][1]);

		switch (resultatMetode)
		{
		case 0: lesTid(i, MMSST);   break;
		case 1: lesTid(i, MMSSHH);	break;
		case 2: lesTid(i, MMSSTTT);	break;
		case 3: lesPoeng(i, 10);    break;
		case 4: lesPoeng(i, 100);   break;
		default:
			break;
		}
	}
	switch (resultatMetode)
	{
	case 0: sorterResultater('t');  break;
	case 1: sorterResultater('t');  break;
	case 2: sorterResultater('t');	break;
	case 3: sorterResultater('p');	break;
	case 4:  sorterResultater('p');	break;
	default:
		break;
	}
	ajourfor();

	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(number, filnavn, ft);
	ofstream utfil(filnavn);

}

void Ovelse::lesTid(int i, const int c)
{
	bool sant = true;
	char temp[MAXTXT + 1];
	int temp2;
	do
	{
		les("\n\tLes inn tid (MMSST):", temp, MMSST);
		if (kunTall(temp))
		{
			temp2 = atoi(temp);
			sant = false;
		}
	} while (sant || (temp2 / 1000 > 59) 
		|| (( (temp2/ 10) % 100) > 59) || (temp2 % 10000) > 9 );
	resultatListe[i][2] = temp2;
}


void Ovelse::lesPoeng(int i, int x)
{
	bool sant = true;
	float temp2;
	char temp[MAXTXT + 1];
	do
	{
		les("\n\tLes inn poeng", temp, MAXTXT);
		if (kunTallFloat)
		{
			temp2 = atof(temp);
			temp2 = (temp2 * x);
			temp2 = int(temp2);
			temp2 = float(temp2);
			temp2 = (temp2 / x);
			resultatListe[i][2] = temp2;
			sant = false;
		}
	} while (sant);
}

void Ovelse::sorterResultater(char hva)
{
	for (int i = 1; i <= antallDeltagere; i++)
	{
		for (int j = i + 1; j <= antallDeltagere; j++)
		{
			if (hva == 'p')
			{
				if (resultatListe[i][2] < resultatListe[j][2])
				{
					sorteringsProsess(i ,j);
				}
			}
			else if (hva == 't')
			{
				if (resultatListe[i][2] > resultatListe[j][2])
				{
					sorteringsProsess(i, j);
				}
			}
		}
	}
}

void Ovelse::sorteringsProsess(int i, int j)
{
	int temp = resultatListe[i][2];
	int temp1 = resultatListe[i][1];
	int temp0 = resultatListe[i][0];

	resultatListe[i][2] = resultatListe[j][2];
	resultatListe[i][1] = resultatListe[j][1];
	resultatListe[i][0] = resultatListe[j][0];

	resultatListe[j][2] = temp;
	resultatListe[j][1] = temp1;
	resultatListe[j][0] = temp0;
}

void Ovelse::ajourfor()
{
	for (int i = 1; i <= antallDeltagere; i++)
	{
		switch (i)
		{
		case 1:ajourfor1(i);
		case 2:ajourfor2(i);
		case 3:ajourfor3(i);
		case 4:ajourfor4(i);
		case 5:ajourfor5(i);
		case 6:ajourfor6(i);

		default:
			break;
		}
	}
}

void Ovelse::ajourfor1(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 7);
	medaljeObjekt.nyMedalje(tempNasjon, gull);
}

void Ovelse::ajourfor2(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 5);
	medaljeObjekt.nyMedalje(tempNasjon, solv);
}

void Ovelse::ajourfor3(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 4);
	medaljeObjekt.nyMedalje(tempNasjon, bronse);
}

void Ovelse::ajourfor4(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 3);
}

void Ovelse::ajourfor5(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 2);
}

void Ovelse::ajourfor6(int i)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 1);
}