#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#pragma warning( disable : 4244 )

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

void Ovelse::flyttStartliste(const int i, const int j)		//Setter i lik verdien til j i arrayen
{
	startListe[i][0] = startListe[j][0];
	startListe[i][1] = startListe[j][1];
}

void Ovelse::nyttDynamiskArray()							//Lager nytt array som er akkurat så langt som det trenger.
{	
	int (*endretStartliste)[2] = new int[antallDeltagere + 1][2]; 

	for (int i = 1; i <= antallDeltagere; i++)				//Går gjennom alle "skuffer" i arrayen
	{
		endretStartliste[i][0] = startListe[i][0];			//Kopierer array fra startliste til endretstartliste
		endretStartliste[i][1] = startListe[i][1];
	}
	delete[] startListe;									//Frigjør startliste i memory
	startListe = endretStartliste;							//Peker startliste på endret startliste
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
		case 'D': endreOvelseDato();		    break; // endrer på dato i øvelse.
		case 'K': endreKlokkeslett();			break; // leser inn nytt klokkeslett via egen funksjon.
		default: cout << "\nHva vil du endre på? (N)avn, (D)ato eller (K)lokkeslett. Q for å avslutte " << endl; break;
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

void Ovelse::skrivStartliste()							//Skriver en startliste til skjerm
{
	char temp[MAXTXT + 1] = "gruppe03/";
	char ch;
	filtype filtype = startliste;

	lagFilNavn(temp, filtype);

	ifstream inn(temp);									//Åpner fil
	if (inn)											//Hvis fila kunne åpnes
	{
		inn >> ch >> antallDeltagere; inn.ignore();		//Les en character og antall deltagere.
		startListe = new int[antallDeltagere + 1][2];	//Lag nytt array som er så langt som trengs
		lesStartlisteFraFil(inn);						//Les startliste fra fil
		for (int i = 1; i <= antallDeltagere; i++)		//Loop gjennom alle deltagere i øvelsen
		{
			cout << "Startnummer: " << i << " ";		//Skriv startnummer
			deltagerobjekt.skrivID(startListe[i][1]);	//Og detaljene om hver deltager
		}
	}
	else
	{
		cout << "\n\tIngen startliste funnet." << endl;
	}
}

void Ovelse::nyStartliste()								//Lager ny startliste
{
	bool finnesAllerede = false;						//Antar at en deltager ikke finnes i øvelsen fra før
	char temp[MAXTXT + 1] = "gruppe03/";
	int deltagerTemp;
	filtype filtype = startliste;

	lagFilNavn(temp, filtype);

	ifstream inn(temp);									//Prøver å åpne fil
	if (!inn)											//Hvis fil ikke kunne åpnes
	{
		antallDeltagere = les("Antall deltagere i denne øvelsen", MINDELTAGER, MAXDELTAGER);
		if (antallDeltagere <= deltagerobjekt.antallDeltagere())	//Hvis det er nok deltagere til å fylle øvelsen
		{
			startListe = new int[antallDeltagere + 1][2];	//Lag ny startliste med plass til alle deltagere i øvelsen
			for (int i = 1; i <= antallDeltagere; i++)		//Går gjennom alle deltagerne som skal være med i øvelsen
			{
				deltagerTemp = les("Deltagernummer", MINDELTAGERE, MAXDELTAGERE);
				if (deltagerobjekt.finnesID(deltagerTemp))	//Skjekker at deltagernummeret tilhører en faktisk deltager
				{
					for (int j = 1; j <= i; j++)		//Går gjennom alle deltagerne i listen så langt
					{
						if (startListe[j][1] == deltagerTemp)	//Hvis deltagernummeret finnes i listen fra før;
						{
							finnesAllerede = true;		//Sett finnesAllerede til sant
						}
					}
					if (!finnesAllerede)				//Hvis den ikke finnes allerede
					{
						startListe[i][0] = i;			//Legg til startnummer
						startListe[i][1] = deltagerTemp;	//og deltagernummer i "skuff" i
						cout << "\n\tDeltager lagt til startlisten." << endl << endl;	//Gi bekreftelse på at deltageren er lagt til
					}
					else
					{
						cout << "\n\tDenne deltageren finnes allerede i denne startlisten" << endl;
						i--;							//Hvis deltageren er i lista fra før, tell ned i med en slik at 
					}									//samme deltager blir lest inn på nytt
				}
				else
				{
					cout << "\n\tIngen deltagere med dette nummeret." << endl;
					i--;								//Hvis det ikke finnes en deltager med dette nummeret;
				}										//tell ned i, slik at samme deltager leses inn på nytt
			}
			skrivStartlisteTilFil();					//Skriv startliste til fil
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

void Ovelse::endreStartliste()							//Legger til, tar bort eller bytter en deltager i startliste
{
	char ressInn[MAXTXT + 1] = "gruppe03/";
	char staInn[MAXTXT + 1] = "gruppe03/";

	filtype resFiltype = resultatliste;
	filtype startinn = startliste;
	lagFilNavn(ressInn, resFiltype);
	lagFilNavn(staInn, startinn);
	ifstream resInn(ressInn);
	ifstream startInn(staInn);

	if (!resInn)										//Hvis det ikke er mulig å åpne resultatliste (den finnes ikke)
	{
		if (startInn)									//og startlisten kan åpnes (den finnes)
		{
			char valg;                //  Brukerens valg.
			skrivMenyOLE();                  //  skriver ut meny med valg.
			lesStartlisteFraFil(startInn);				//Leser startlisten inn i memory

			valg = les();             //  Leser brukerens valg.
			while (valg != 'Q') {
				switch (valg) {
				case 'S': minusStartlisteDeltager();	break;
				case 'N': plussStartlisteDeltager();	break;
				case 'B': byttStartlisteDeltager();		break;
				default:  skrivMenyOLE();				break;
				}
				valg = les();
			}
			skrivStartlisteTilFil();
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

void Ovelse::minusStartlisteDeltager()					//Trekker fra en deltager i en startliste
{
	bool deltagerFinnesIkke = true;						//Går ut ifra at deltageren ikke finnes
	int deltagerTemp, i = 1;
	deltagerTemp = les("Deltagernummeret du vil fjerne fra startlisten", MINDELTAGERE, MAXDELTAGERE);
	while(deltagerFinnesIkke && i <= antallDeltagere)	//Mens deltageren ikke finnes og det ikke er gått gjennom alle deltagere
	{
		if (startListe[i][1] == deltagerTemp)			//Hvis deltager finnes i lista
		{
			flyttStartliste(i, antallDeltagere);		//Flytt siste deltager inn over i
			antallDeltagere--;							//Tell ned antall deltagere
			nyttDynamiskArray();						//Lag nytt array 
			deltagerFinnesIkke = false;					//Set at det ble funnet deltager (dobbel negativ = positiv)
			cout << "\n\tDeltager fjernet fra startliste." << endl << endl;
		}
		i++;											//Teller opp i
	}
	if (deltagerFinnesIkke)								//Hvis deltager ikke ble funnet
	{
		cout << "\n\tFant ingen deltagere med dette nummeret" << endl;
	}
	skrivStartlisteTilFil();							//Skriv ny startliste til fil
}

void Ovelse::plussStartlisteDeltager()					//Legg til en deltager i startlisten
{
	bool finnesAllerede = false;						//Gå ut ifra at deltageren ikke er i listen allerede
	int deltagerTemp;
	deltagerTemp = les("Deltagernummeret du vil legge til startlisten", MINDELTAGERE, MAXDELTAGERE);
	if (deltagerobjekt.finnesID(deltagerTemp))			//Skjekk at deltagernummeret tilhører en deltager
	{
		for (int i = 1; i <= antallDeltagere; i++)		//Gå gjennom startlisten
		{
			if (startListe[i][1] == deltagerTemp)		//Hvis deltagernummeret finnes
			{
				finnesAllerede = true;					//Sett finnesAllerede til sant
			}
		}
		if (!finnesAllerede)							//Hvis den ikke finnes allerede
		{
			antallDeltagere++;							//Tell opp antall deltagere
			nyttDynamiskArray();						//Lag nytt array
			startListe[antallDeltagere][0] = antallDeltagere;	//Legg til ny deltager i arrayet
			startListe[antallDeltagere][1] = deltagerTemp;		//----------^^------------------
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
	skrivStartlisteTilFil();								//Skriv startliste til fil
}

void Ovelse::byttStartlisteDeltager()						//Bytter ut en deltager med en annen
{
	bool finnesNyDeltager = false;							//Antar at den nye deltageren ikke er i listen allerede
	int finnesIStartliste = 0, deltagerTemp, nyDeltagerTemp, i;

	deltagerTemp = les("Deltagernummeret du vil bytte ut av startlisten", MINDELTAGERE, MAXDELTAGERE);
	for (i = 1; i <= antallDeltagere; i++)					//Går gjennom startlisten
	{
		if (startListe[i][1] == deltagerTemp)				//Hvis deltageren finnes i listen
		{
			finnesIStartliste = i;							//Sett finnesIStartliste til indeksen der deltageren er
		}
	}
	if (finnesIStartliste)									//Hvis den finnes i startliste (variablen != 0)
	{
		nyDeltagerTemp = les("Deltagernummer du vil erstatte inn i startlisten", MINDELTAGERE, MAXDELTAGERE);
		if (deltagerobjekt.finnesID(nyDeltagerTemp))		//Skjekk om ny deltager er en faktisk deltager
		{
			for (i = 1; i <= antallDeltagere; i++)			//Gå gjennom alle deltagere i lista
			{
				if (startListe[i][1] == nyDeltagerTemp)		//Skjekk om ny deltager finnes i lista fra før
				{
					finnesNyDeltager = true;				//Ny deltager finnes i lista
				}
			}
		}

	}
	else
	{
		cout << "\n\tFant ingen brukere med dette dalagernummeret i startlisten." << endl;
	}
	if (finnesIStartliste && !finnesNyDeltager)				//Hvis deltageren finnes i startlista og ny deltager IKKE finnes i lista
	{
		startListe[finnesIStartliste][1] = nyDeltagerTemp;	//Sett den første deltageren like den nye deltageren, overskriv 
		cout << "\n\tDeltager erstattet i startliste" << endl << endl;
	}
	skrivStartlisteTilFil();								//Skriv startlisten til fil
}

void Ovelse::fjernDeltagerliste()							//Fjerner startlisten hvis den eksisterer
{
	char ressInn[MAXTXT + 1] = "gruppe03/";
	char staInn[MAXTXT + 1] = "gruppe03/";

	filtype ft = resultatliste;
	filtype startinn = startliste;
	lagFilNavn(ressInn, ft);
	lagFilNavn(staInn, startinn);
	ifstream resInn(ressInn);
	ifstream startInn(staInn);

	if (startInn)											//Prøver å åpne startlisten (den eksisterer)
	{
		if (!resInn)										//Hvis resultatlisten IKKE finnes
		{
			cout << "\n\tEr du sikker på at du vil slette startlisten for denne øvelsen? (Y/n)";
			char ch = les();
			if (ch == 'Y')									//Y for å slette, alle andre input tas som nei
			{
				startInn.close();							//Lukker fila
				if (remove(staInn) == 0)					//Skjekker om fila kunne sletter, hvis ja
				{
					cout << "\n\tStartliste fjernet." << endl;	//Bekreftelse
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

void Ovelse::fjernOvelse()
{
	delete[] ovelseNavn;
	slettResultatListe();
	fjernDeltagerliste();
	delete[] resultatListe;
	delete[] startListe;
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

void Ovelse::lesStartlisteFraFil(ifstream & inn)			//Leser startliste fra fil
{
	for (int i = 1; i <= antallDeltagere; i++)				//Går gjennom alle deltagere
	{
		inn >> startListe[i][0] >> startListe[i][1];		//Leser inn i riktig "skuff" i startliste arrayen
		inn.ignore();										//Ignorerer linjeshift
	}
}

void Ovelse::skrivStartlisteTilFil()						//Skriver startliste til fil
{
	filtype start = startliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn( filnavn, start);

	ofstream ut(filnavn);									//Lager/åpner fil
	ut << "I " << antallDeltagere << endl;					//Skriver I for ikke sortert og antallDeltagere
	for (int i = 1; i <= antallDeltagere; i++)				//Går gjennom alle deltagere
	{
		ut << startListe[i][0] << " " << startListe[i][1] << endl;	//Skriver disse til fil
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
		case 0: resultatListe[i][2] = lesTid(i, MMSST);   break;
		case 1: resultatListe[i][2] =  lesTid(i, MMSSHH);	break;
		case 2: resultatListe[i][2] = lesTid(i, MMSSTTT);	break;
		case 3: resultatListe[i][2] = lesPoeng(i, POENGX);    break;
		case 4: resultatListe[i][2] = lesPoeng(i, POENGXX);   break;
		default:
			break;
		}
	}

	bool alleBrutt = true;

	for (int g = 1; g <= antallDeltagere; g++)
	{
		if (resultatListe[g][2] > 0)
		{
			alleBrutt = false;
		}
	}
	if (!alleBrutt)
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
	skrivSortertResultatListe();
}

void Ovelse::skrivTid(int in)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0];
		if (resultatListe[m][2] > 0)
		{
			cout << " \tTid: " << int(resultatListe[m][2] / (in * 100)) << ":" << (int(resultatListe[m][2] / in) % 100) << ":" << (int(resultatListe[m][2]) % in) << endl;
		}
		else
		{
			cout << "\tUgyldig tid pga brutt/disket/ikke møtt opp." << endl;
		}
	}
}

void Ovelse::skrivPoeng(int t)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0];
			if (true)
			{
				cout << " \tPoeng: " << int(resultatListe[m][2] / t) << "." << (int(resultatListe[m][2]) % t) << endl;
			}
			else
			{
				cout << "\tUgyldig poeng pga brutt/disket/ikke møtt opp." << endl;
			}
	}
}



int Ovelse::lesTid(int i, const int c)
{	
	bool sant = true;
	char temp[MAXTXT + 1];
	int temp2;
	do
	{
		les("\n\tLes inn tid (MMSST), eller B for brutt/disket/ikke møtt opp", temp, MAXTXT);
		if (!(strcmp(temp, "B") || !(strcmp(temp, "b"))))
		{
			return (-1);
		}
		else if (kunTall(temp))
		{
			temp2 = atoi(temp);
			sant = false;
		}
	} while (sant || ((temp2 / (c*100)) > 59)
		|| (( (temp2/ c) % 100) > 59) || (temp2 % c) > int(c*0.999) );
	return(temp2);
}


int Ovelse::lesPoeng(int i, int x)
{
	bool sant = true;
	float temp2;
	char temp[MAXTXT + 1];
	do
	{
		les("\n\tLes inn poeng eller B for brutt/disket/ikke møtt opp", temp, MAXTXT);
		if (!(strcmp(temp, "B") || !(strcmp(temp, "b"))))
		{
			return(-1);
		}
		if (kunTallFloat(temp))
		{
			temp2 = atof(temp);
			temp2 = (temp2 * x);
			temp2 = int(temp2);
			temp2 = float(temp2);
			temp2 = (temp2 / x);
			return(temp2);
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
			while (resultatListe[i][2] < 0)
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
	if (resultatListe[i][2]> 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 7, oppned);
		medaljeObjekt.endreMedalje(tempNasjon, gull, oppned);
	}
}

void Ovelse::ajourfor2(int i, plusminus oppned)
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 5, oppned);
		medaljeObjekt.endreMedalje(tempNasjon, solv, oppned);
	}
}

void Ovelse::ajourfor3(int i, plusminus oppned)
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 4, oppned);
		medaljeObjekt.endreMedalje(tempNasjon, bronse, oppned);
	}
}

void Ovelse::ajourfor4(int i, plusminus oppned)
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 3, oppned);
	}
}

void Ovelse::ajourfor5(int i, plusminus oppned)
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 2, oppned);
	}
}

void Ovelse::ajourfor6(int i, plusminus oppned)
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 1, oppned);
	}
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
	else
	{
		cout << "\n\tResutatliste finnes ikke!" << endl;
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
