#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>

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
}

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
	bool finnesAllerede = false;
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
					for (int j = 1; j <= i; j++)
					{
						if (startListe[j][1] == deltagerTemp)
						{
							finnesAllerede = true;
						}
					}
					if (!finnesAllerede)
					{
						startListe[i][0] = i;
						startListe[i][1] = deltagerTemp;
						cout << "\n\tDeltager lagt til startlisten." << endl << endl;
					}
					else
					{
						cout << "\n\tDenne deltageren finnes allerede i denne startlisten" << endl;
					}
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
	char ressInn[MAXTXT + 1] = "gruppe03/";
	char staInn[MAXTXT + 1] = "gruppe03/";

	filtype ft = resultatliste;
	filtype startinn = startliste;
	lagFilNavn(ressInn, ft);
	lagFilNavn(staInn, startinn);
	ifstream resInn(ressInn);
	ifstream startInn(staInn);

	if (!resInn)
	{
		if (startInn)
		{
			char valg;                //  Brukerens valg.
			skrivMenyOLE();                  //  skriver ut meny med valg.

			valg = les();             //  Leser brukerens valg.
			while (valg != 'Q') {
				switch (valg) {
				case 'S': minusStartlisteDeltager();	break;
				case 'N': plussStartlisteDeltager();	break;
				case 'F': byttStartlisteDeltager();		break;
				default:  skrivMenyOLE();				break;
				}
				valg = les();
			}
		}
		else
		{
			cout << "\n\tStartliste finnes ikke." << endl;
		}
	}
	else
	{
		cout << "\n\tResultatliste finnes." << endl;
	}
}

void Ovelse::minusStartlisteDeltager()
{
	bool fantDeltager = false;
	int deltagerTemp, i = 1;
	deltagerTemp = les("Deltagernummeret du vil fjerne fra startlisten", MINDELTAGERE, MAXDELTAGERE);
	while(!fantDeltager && i <= antallDeltagere)
	{
		if (startListe[i][1] == deltagerTemp)
		{
			flyttStartliste(antallDeltagere, i);
			antallDeltagere--;
			nyttDynamiskArray();
			fantDeltager = true;
			cout << "Deltager fjernet fra startliste." << endl << endl;
		}
		i++;
	}
	if (!fantDeltager)
	{
		cout << "\n\tFant ingen deltagere med dette nummeret" << endl;
	}
	skrivStartlisteTilFil();
}

void Ovelse::plussStartlisteDeltager()
{
	bool finnesAllerede = false;
	int deltagerTemp;
	deltagerTemp = les("Deltagernummeret du vil legge til startlisten", MINDELTAGERE, MAXDELTAGERE);
	if (deltagerobjekt.finnesID(deltagerTemp))
	{
		for (int i = 1; i <= antallDeltagere; i++)
		{
			if (startListe[i][1] == deltagerTemp)
			{
				finnesAllerede = true;
			}
		}
		if (!finnesAllerede)
		{
			antallDeltagere++;
			nyttDynamiskArray();
			startListe[antallDeltagere][0] = antallDeltagere;
			startListe[antallDeltagere][1] = deltagerTemp;
			cout << "\n\tDeltager lagt til i startliste" << endl << endl;
		}
		else
		{
			cout << "\n\tDen nye deltageren er allerede i startlista." << endl;
		}
	}
	else
	{
		cout << "\n\tDet finnes ikke noen deltagere med dette nummeret." << endl;
	}
	skrivStartlisteTilFil();
}

void Ovelse::byttStartlisteDeltager()
{
	bool finnesNyDeltager = false;
	int finnesIStartliste = 0, deltagerTemp, nyDeltagerTemp, i;

	deltagerTemp = les("Deltagernummeret du vil bytte ut av startlisten", MINDELTAGERE, MAXDELTAGERE);
	for (i = 1; i <= antallDeltagere; i++)
	{
		if (startListe[i][1] == deltagerTemp)
		{
			finnesIStartliste = i;
		}
	}
	if (finnesIStartliste)
	{
		nyDeltagerTemp = les("Deltagernummer du vil erstatte inn i startlisten", MINDELTAGERE, MAXDELTAGERE);
		if (deltagerobjekt.finnesID(nyDeltagerTemp))
		{
			for (i = 1; i <= antallDeltagere; i++)
			{
				if (startListe[i][1] == nyDeltagerTemp)
				{
					finnesNyDeltager = true;
				}
			}
		}

	}
	else
	{
		cout << "\n\tFant ingen brukere med dette dalagernummeret i startlisten." << endl;
	}
	if (finnesIStartliste && !finnesNyDeltager)
	{
		startListe[finnesIStartliste][1] = nyDeltagerTemp;
		cout << "\n\tDeltager erstattet i startliste" << endl << endl;
	}
	skrivStartlisteTilFil();
}

void Ovelse::fjernDeltagerliste()
{
	char ressInn[MAXTXT + 1] = "gruppe03/";
	char staInn[MAXTXT + 1] = "gruppe03/";

	filtype ft = resultatliste;
	filtype startinn = startliste;
	lagFilNavn(ressInn, ft);
	lagFilNavn(staInn, startinn);
	ifstream resInn(ressInn);
	ifstream startInn(staInn);

	if (startInn)
	{
		if (!resInn)
		{
			cout << "\n\tEr du sikker på at du vil slette startlisten for denne øvelsen? (Y/n)";
			char ch = les();
			if (ch == 'Y')
			{
				startInn.close();
				if (remove(staInn) == 0)
				{
					cout << "\n\tStartliste fjernet." << endl;
				}
				else
				{
					cout << "Klarte ikke å slette listen." << endl;
				}
			}
		}
		else
		{
			cout << "\n\tResultatliste allerede laget." << endl;
		}
	}
	else
	{
		cout << "\n\tFant ingen startliste." << endl;
	}
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
		case 'S': skrivResultatliste(); break;
		case 'N': nyResultatliste();  break;
		case 'F': slettResultatListe();  break;
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
	lagFilNavn( filnavn, ft);

	lagFilNavn(filnavn, ft);

	ofstream ut(filnavn);
	ut << "I " << antallDeltagere << endl;
	for (int i = 1; i <= antallDeltagere; i++)
	{
		ut << startListe[i][0] << " " << startListe[i][1] << endl;
	}
}

void Ovelse::nyResultatliste()
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	ifstream inn(filnavn);
	if (!inn)
	{
		inn.close();
		filtype ft = startliste;
		char filnavn2[MAXTXT + 1] = "gruppe03/";
		lagFilNavn(filnavn2, ft);
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
	for (int i = 1; i <= antallDeltagere; i++)
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
		case 3: lesPoeng(i, POENGX);    break;
		case 4: lesPoeng(i, POENGXX);   break;
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

	
	switch (resultatMetode)
	{
	case 0: skrivTid(MMSST);		break;
	case 1: skrivTid(MMSSHH);		break;
	case 2: skrivTid(MMSSTTT);	break;
	case 3: skrivPoeng(POENGX);	break;
	case 4: skrivPoeng(POENGXX);	break;
	default:
		break;
	}
	ajourfor(pluss);
	skrivSortertResultatListe();
}

void Ovelse::skrivTid(int in)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0]
			<< " \tTid: " << int(resultatListe[m][2]/ (in*100)) << ":" << (int(resultatListe[m][2]/in) % 100) << ":" << (int(resultatListe[m][2]) % in) << endl;
	}
}

void Ovelse::skrivPoeng(int t)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0]
			<< " \tPoeng: " << int(resultatListe[m][2] / t) << "." << (int(resultatListe[m][2]) % t) << endl;
	}
}



void Ovelse::lesTid(int i, const int c)
{	
	bool sant = true;
	char temp[MAXTXT + 1];
	int temp2;
	do
	{
		les("\n\tLes inn tid (MMSST)", temp, MAXTXT);
		if (kunTall(temp))
		{
			temp2 = atoi(temp);
			sant = false;
		}
	} while (sant || ((temp2 / (c*100)) > 59) 
		|| (( (temp2/ c) % 100) > 59) || (temp2 % c) > int(c*0.999) );
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

void Ovelse::ajourfor(plusminus oppned)
{
	for (int i = 1; i <= antallDeltagere; i++)
	{
		switch (i)
		{
		case 1:ajourfor1(i, oppned); break;
		case 2:ajourfor2(i, oppned); break;
		case 3:ajourfor3(i, oppned); break;
		case 4:ajourfor4(i, oppned); break;
		case 5:ajourfor5(i, oppned); break;
		case 6:ajourfor6(i, oppned); break;

		default:
			break;
		}
	}
}

void Ovelse::ajourfor1(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 7, oppned);
	medaljeObjekt.endreMedalje(tempNasjon, gull, oppned);
}

void Ovelse::ajourfor2(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 5, oppned);
	medaljeObjekt.endreMedalje(tempNasjon, solv, oppned);
}

void Ovelse::ajourfor3(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 4, oppned);
	medaljeObjekt.endreMedalje(tempNasjon, bronse, oppned);
}

void Ovelse::ajourfor4(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 3, oppned);
}

void Ovelse::ajourfor5(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 2, oppned);
}

void Ovelse::ajourfor6(int i, plusminus oppned)
{
	char tempNasjon[LANDSKODE];
	deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
	poengobjekt.oppdaterPoeng(tempNasjon, 1, oppned);
}

void Ovelse::slettResultatListe()
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);
	ifstream inn(filnavn);
	if (inn)
	{
		char sortertemp;
		inn >> sortertemp;
		inn >> antallDeltagere; inn.ignore();
		resultatListe = new float[antallDeltagere + 1][3];
		slettStatistikk(inn, sortertemp);
		inn.close();
		if (remove(filnavn) == 0) {
			cout << "\n\tResultatliste slettet!" << endl;
		}
	}
	else
	{
		cout << "\n\tFinner ikke resultatliste." << endl;
	}
}

void Ovelse::slettStatistikk(ifstream & inn, char ch)
{
	for (int  i = 1; i <= antallDeltagere; i++)
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1] >> resultatListe[i][2]; inn.ignore();
	}
	if (ch == 'I') 
	{
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
	}
	ajourfor(minusssssssss);
}

void Ovelse::skrivResultatliste()
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);
	ifstream inn(filnavn);
	if (inn)
	{
		char sortertemp;
		inn >> sortertemp;
		inn >> antallDeltagere; inn.ignore();
		resultatListe = new float[antallDeltagere + 1][3];
		lagStatistikk(inn, sortertemp);
		inn.close();
		remove(filnavn);
		skrivSortertResultatListe();
	}
}

void Ovelse::lagStatistikk(ifstream & inn, char ch)
{
	for (int i = 1; i <= antallDeltagere; i++)
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1] >> resultatListe[i][2]; inn.ignore();
	}

	if (ch == 'I')
	{
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
	}

	switch (resultatMetode)
	{
	case 0: skrivTid(MMSST);		break;
	case 1: skrivTid(MMSSHH);		break;
	case 2: skrivTid(MMSSTTT);	break;
	case 3: skrivPoeng(POENGX);	break;
	case 4: skrivPoeng(POENGXX);	break;
	default:
		break;
	}

	ajourfor(pluss);

}

void Ovelse::skrivSortertResultatListe()
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);
	ofstream utfil(filnavn);
	utfil << "S" << " " << antallDeltagere << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		utfil << resultatListe[m][0] << " " << resultatListe[m][1] << " " << resultatListe[m][2] << endl;
	}
}
