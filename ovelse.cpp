#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#pragma warning( disable : 4244 )		//Disable warning om at det mister data ved konvertering mellom float og int
//da dette er poenget.

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

Ovelse::Ovelse(int i, char chr[], resultatType rt) : NumElement(i)	// leser inn data til øvelse objekt.
{
	ovelseNavn = new char[strlen(chr) + 1];							// oppretter et nytt array med akkurat den lengden man trenger.
	strcpy(ovelseNavn, chr);										// kopierer navn over i den nye arrayen
	klokkeStart = lesKlokkeSlett();									// leser inn klokkeslett via egen funksjon.
	dato = lesDato();												// leser inn dato via egen funksjon.
	antallDeltagere = 0;											// antall deltagere er 0 intil en deltager blir lagt til.
	resultatMetode = rt;											// går fra 1-6.
}

void Ovelse::skrivMenyOE()
{
	cout << "\n\nHva vil du endre:"
		<< "\n\tN = Navn"
		<< "\n\tD = Dato"
		<< "\n\tK = Klokkeslett"
		<< "\n\tQ = Forrige meny";
}

void Ovelse::endreOvelsen()
{
	skrivMenyOE();
	char ch = les();	// leser inn en uppercase tegn
	while (ch != 'Q')	// sjekker at brukeren ikke vil avslutte
	{
		switch (ch)		// Utfører brukerens valg
		{
		case 'N': endreNavn();			break; // sletter først navn, så leser inn nytt
		case 'D': endreOvelseDato();	break; // endrer på dato i øvelse.
		case 'K': endreKlokkeslett();	break; // leser inn nytt klokkeslett via egen funksjon.
		default: skrivMenyOE();			break;
		}
		skrivMenyOE();
		ch = les();
	}
}

void Ovelse::endreNavn()	// sletter først det gamle navnet, så leser inn et nytt.
{
	delete[] ovelseNavn; les("\n\tLes inn nytt navn", ovelseNavn);
}

void Ovelse::endreOvelseDato()		// leser inn dato på nytt.
{
	dato = lesDato();
}

void Ovelse::endreKlokkeslett()		// leser inn klokkelsett på nytt.
{
	klokkeStart = lesKlokkeSlett();
}

void Ovelse::skrivAlt()		// skriver ut alle data om en øvelse.
{
	cout << "\n\tNummer: " << number 
		<< "\n\tNavn: " << ovelseNavn 
		<< "\n\tDato: " << dato 
		<< "\n\tKlokkeslett: " << klokkeStart 
		<< "\n\tAntall Deltagere: " << antallDeltagere << endl;
}

bool Ovelse::sjekkNavn(char c[])		// sjekker om en øvelse har samme navn som det brukeren skrev inn.
{
	return(!strcmp(c, ovelseNavn));
}

bool Ovelse::sjekkID(int i)			// sjekker om en øvelse har samme id som brukeren skrev inn.
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
		delete[] startListe;
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
			delete[] startListe;						//Frigjør plassen til startliste i memory
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
				skrivMenyOLE();
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
			cout << "\n\tKan ikke slette startliste, da resultatliste allerede er laget." << endl;
		}
	}
	else
	{
		cout << "\n\tFant ingen startliste." << endl;
	}
}

void Ovelse::skrivTilFil(ofstream &ut)			// skriver alle øvelsens data til fil.
{
	ut << number << '\n' << ovelseNavn << '\n'
		<< klokkeStart << " " << dato << " " << antallDeltagere << endl;
}

Ovelse::Ovelse(ifstream & inn, int i, resultatType rs) : NumElement (i)		// leser alle øvelsens data fra fil.
{
	lesInnFraFil(ovelseNavn, inn);											// egen les funksjon for å lese inn i en peker.
	inn >> klokkeStart >> dato >> antallDeltagere; inn.ignore();
	resultatMetode = rs;
}

void Ovelse::fjernOvelse()		// sletter alle øvelsens data som må slettes, alle som har blitt opprettet med "new".
{
	delete[] ovelseNavn;		// sletter navnet.
	slettResultatListe();		// sletter resultatlista via dens egen remove funksjon.
	fjernDeltagerliste();		// sletter så deltagerlista via dens egen remove funksjon.
	delete[] resultatListe;		// sletter arrayen resultatliste.
	delete[] startListe;		// sletter arrayn startiste.
}

void Ovelse::lagFilNavn(char ch[], filtype ft)	// lager alle filnavn for å lese fra/skrive til fil.
{
	char temp[MAXTXT + 1] = "OV";			// lager en ny array med "'ov" på starten.
	char temp2[MAXTXT + 1];
	_itoa(number, temp2, 10);				// gjør om char til int. 
	
	//char temp[MAXTXT + 1] = (ft == startliste) ?  ".STA" : ".RES";	// TIL SENERE INSPEKSJON, HJELP BLIR SATT PRIS PÅ *HINT HINT*

	if (ft == startliste)		// kjøres hvis det er en startliste som tilkaller funksjonen.
	{
		char temp3[MAXTXT + 1] = ".STA";	// legges til på slutten.
		strcat(ch, temp);	//legger til OV
		strcat(ch, temp2);	// skøter på nummer (eks 1000)
		strcat(ch, temp3);	// skøter på .STA.
	}
	else				// kjøres hvis det er en resultatliste.
	{ 
		char temp3[MAXTXT + 1] = ".RES"; // legges til på slutten.
		strcat(ch, temp);	//legger til OV
		strcat(ch, temp2);	// skøter på nummer.
		strcat(ch, temp3);	// skøter på .RES
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
		skrivMenyOR();
		valg = les();
	}
}

void Ovelse::skrivMenyOR()			// skriver alle valgene mulig i resultatliste menyen.
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS = Skriv resultatliste"
		<< "\n\tN = Ny resultatliste" 
		<< "\n\tF = Fjerne resultatliste"
		<< "\n\tQ = Forrige meny";
}

void Ovelse::skrivMenyOLE()			// skriver alle valgene mulig i startliste menyen.
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

void Ovelse::nyResultatliste()				// lager en ny resultatliste utifra innlest deltagerliste.
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, resultatliste);
	ifstream inn(filnavn);		// sjekker om det allerde finnes en resultatliste.
	if (!inn)
	{
		inn.close(); // lukker fila igjen.
		filtype ft = startliste;
		char filnavn2[MAXTXT + 1] = "gruppe03/";
		lagFilNavn(filnavn2, ft);
		ifstream innfil(filnavn2); // åpner statrlista.
		if (innfil)					// sjekker om fila ble åpnet.
		{
			char sortertemp;		// leser inn om den er sortert eller ikke.
			innfil >> sortertemp;
			innfil >> antallDeltagere;	// leser inn antall deltagere på fila.
			resultatListe = new float[antallDeltagere + 1][3];	// lager en ny array til deltagerne.
			lagResultat(innfil);				// sender det videre til ny funksjon.
			delete[] resultatListe;				//Frigjør resultatliste i memory
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


void Ovelse::lagResultat(ifstream & inn)					// lager selve resultatlista.
{
	for (int i = 1; i <= antallDeltagere; i++)				// looper gjennom alle deltagere som ble lest inn.
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1];	// legger startnummer og deltagernummer inn i arrayen.
		inn.ignore();

		cout << "\n\tStartnummer: " << resultatListe[i][0];				//skriver ut info om deltageren.
		deltagerobjekt.skrivDeltagerStart(resultatListe[i][1]);

		switch (resultatMetode)											// switch som bestemmer om resultat skal leses inn som tide eller poeng.
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

	bool alleBrutt = true;	// sjekker om alle deltagerne har brutt, fordi da skal det ikke sorteres. grunnen er at sorteringa blir da en evig loop.

	for (int g = 1; g <= antallDeltagere; g++)
	{
		if (resultatListe[g][2] > 0)	// sjekker om resultatet er et neativt tall. fordi -1 = brutt.
		{
			alleBrutt = false;
		}
	}
	if (!alleBrutt) // kjøres hvis minst 1 deltager har fullført med gyldig resultat
	{
		switch (resultatMetode)					// switch som sorterer utifra om det er tid eller poeng.
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
	
	switch (resultatMetode)						// switch som skriver resultatet utifra om det er tid eller poeng.
	{
	case 0: skrivTid(MMSST);		break;
	case 1: skrivTid(MMSSHH);		break;
	case 2: skrivTid(MMSSTTT);	break;
	case 3: skrivPoeng(POENGX);	break;
	case 4: skrivPoeng(POENGXX);	break;
	default:
		break;
	}
	ajourfor(pluss);						// tildeler medaljer og poeng.
	skrivSortertResultatListe();			// opprettetr selve resultatliste-fila og skriver data til den.
}

void Ovelse::skrivTid(int in)				// skriver ut tid basert på medsendt variabel (MMSST / MMSSHH/ MMSSTTT)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0];
		if (resultatListe[m][2] > 0) // sjekker om en deltagers resultat er gyldig før det skrives ut.
		{
			cout << " \tTid: " << int(resultatListe[m][2] / (in * 100))  // deler med 100 * medsent for å få tak de to første siffrene i det innleste tallet.
				<< ":" << (int(resultatListe[m][2] / in) % 100)			// delet først med medsendt verdi, så modder med 100 for å få tak i de midterste siffrene i tallet.
				<< ":" << (int(resultatListe[m][2]) % in) << endl;		// modder det med medsendt verdi for å få tak i det/de bakerste siffrene i tallet.
		}
		else
		{
			cout << "\tUgyldig tid pga brutt/disket/ikke møtt opp." << endl;
		}
	}
}

void Ovelse::skrivPoeng(int t)								// skriver ut poeng ufifra medsend variabel (poengX / poengXX)
{
	cout << "\n\n\tResultatliste for: " << ovelseNavn << endl;
	for (int m = 1; m <= antallDeltagere; m++)
	{
		cout << "\n\tNummer: " << m << " \tDeltager: " << resultatListe[m][1]
			<< " \tStartnummer: " << resultatListe[m][0];
			if (true)	// sjekker om resultater er gyldig.
			{
				cout << " \tPoeng: " << int(resultatListe[m][2] / t)	// deler med medsendt verdi for å få tak i siffer før komma.
					<< "." << (int(resultatListe[m][2]) % t) << endl;	// modder med medsendt verdi for å få tak i siffer bak komma.
			}
			else
			{
				cout << "\tUgyldig poeng pga brutt/disket/ikke møtt opp." << endl;
			}
	}
}



int Ovelse::lesTid(int i, const int c)			// leser inn resultat som tid.
{	
	bool sant = true;
	char temp[MAXTXT + 1];
	int temp2;
	do
	{
		les("\n\tLes inn tid (MMSST), eller B for brutt/disket/ikke møtt opp", temp, MAXTXT);
		if (!(strcmp(temp, "B") || !(strcmp(temp, "b"))))	// sjekker om brukeren skrev inn B for brutt.
		{
			return (-1);		// brutt har verdien -1.
		}
		else if (kunTall(temp))		// sjekker om det ble lest inn bare tall.
		{
			temp2 = atoi(temp);	// gjor om char til int.
			sant = false;
		}
	} while (sant || ((temp2 / (c*100)) > 59)							// sikrer at innlest tidspunkt er innenfor et gyldig spektrum.
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
		if (!(strcmp(temp, "B") || !(strcmp(temp, "b")))) // sjekker om deltager har brutt.
		{
			return(-1); // brutt = -1.
		}
		if (kunTallFloat(temp)) // sjekker om det er bare tall.
		{
			temp2 = atof(temp); // gjør om fra char til float.
			temp2 = (temp2 * x); // ganger med 10/100 for å bare beholde 1 eller 2 siffre som var bak komma.
			temp2 = int(temp2);		// gjør det om til int for å kaste de andre siffrene.
			temp2 = float(temp2);	// gjør det om igjen til float for å kunne få deismaltall.
			temp2 = (temp2 / x);	// delet det med 10/100 for å flytte tallene bak komma igjen.
			return(temp2);
			sant = false;
		}
	} while (sant);			// kjøres helt til brukeren har lest inn et gyldig resultat
}

void Ovelse::sorterResultater(char hva)				// sorterer resultater basert på type,
{
	for (int i = 1; i <= antallDeltagere; i++)		// teller opp første arrayskuff.
	{
		for (int j = i + 1; j <= antallDeltagere; j++)	// teller op andre arrayskuff.
		{
			if (hva == 'p')								// hvis det er poeng.
			{
				if (resultatListe[i][2] < resultatListe[j][2])	// skal den største først.
				{
					sorteringsProsess(i ,j);		// selve sorteringsprosessen som flytter ting.
				}
			}
			else if (hva == 't')				// hvis det er tid
			{
				if (resultatListe[i][2] > resultatListe[j][2])	// skal den minste veriden først.
				{
					sorteringsProsess(i, j);	//flytteprossessen.
				}
			}
			while (resultatListe[i][2] < 0)		// hvis veriden er -1, aka deltager har brutt, skal deltageren flyttes nederst på resultatlista.
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

void Ovelse::sorteringsProsess(int i, int j)  // selve flyttingsprosessen der i og j skuffene blir byttet.
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

void Ovelse::ajourfor(plusminus oppned) // tar enten pluss eller minus for så å oppdatere medaljer og poeng utifra dette.
{
	for (int i = 1; i <= antallDeltagere; i++) // kjører til antall deltagere slik at det bare blir oppdatert på deltagere som finnes.
	{
		switch (i)
		{
		case 1:ajourfor1(i, oppned); break;	// oppdaterer for 1 plass
		case 2:ajourfor2(i, oppned); break;	// 2 plass
		case 3:ajourfor3(i, oppned); break;	// 3 plass
		case 4:ajourfor4(i, oppned); break;	// 4 plass
		case 5:ajourfor5(i, oppned); break;	// 5 plass
		case 6:ajourfor6(i, oppned); break;	// 6 plass.

		default:
			break;
		}
	}
}

void Ovelse::ajourfor1(int i, plusminus oppned)			// tar pluss eller minus og sender det videre til medalje og poeng.
{
	if (resultatListe[i][2]> 0)		// sjekker at resultatet er gyldig, slik at en som har brutt ikke får noe medalje/poeng.
	{
		char tempNasjon[LANDSKODE];				// henter landskoden fra deltageren.
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 7, oppned);		// oppdaterer poeng.
		medaljeObjekt.endreMedalje(tempNasjon, gull, oppned);	// oppdaterer medaljer.
	}
}

void Ovelse::ajourfor2(int i, plusminus oppned)		// samme som overnfor, bare for 2 plass.
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 5, oppned);
		medaljeObjekt.endreMedalje(tempNasjon, solv, oppned);
	}
}

void Ovelse::ajourfor3(int i, plusminus oppned)		// samme for 3 plass.
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 4, oppned);
		medaljeObjekt.endreMedalje(tempNasjon, bronse, oppned);
	}
}

void Ovelse::ajourfor4(int i, plusminus oppned)		// 4 plass.
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 3, oppned);
	}
}

void Ovelse::ajourfor5(int i, plusminus oppned)		// 5 plass.
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 2, oppned);
	}
}

void Ovelse::ajourfor6(int i, plusminus oppned)		// 6 plass.
{
	if (resultatListe[i][2] > 0)
	{
		char tempNasjon[LANDSKODE];
		deltagerobjekt.hentNasjon(tempNasjon, resultatListe[i][1]);
		poengobjekt.oppdaterPoeng(tempNasjon, 1, oppned);
	}
}

void Ovelse::slettResultatListe()		// sjekker om det finnes en resultatliste, for så å slette den og oppdaterer statistikk.
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);
	ifstream inn(filnavn);		// prøver å åpne resultatliste.
	if (inn)					// hvis den ble åpna.
	{
		char sortertemp;		// sjekker om den var sortert.
		inn >> sortertemp;		
		inn >> antallDeltagere; inn.ignore();	// leser in antall deltagere.
		resultatListe = new float[antallDeltagere + 1][3];	// legger deltagrne inn i ny array som blir opprettet.
		slettStatistikk(inn, sortertemp);	// ny funksjon som sletter alle medaljer og poeng fra resultatlista som skal slettes.
		inn.close();	// lukker filen.
		delete[] resultatListe;	//Frigjør arrayens plass i memory
		if (remove(filnavn) == 0) {	// sletter filen og retunerer om filen ble sletta.
			cout << "\n\tResultatliste slettet!" << endl;
		}
	}
	else // hvis filen ikke kunne åpnes.
	{
		cout << "\n\tFinner ikke resultatliste." << endl;
	}
}

void Ovelse::slettStatistikk(ifstream & inn, char ch)			// sletter medaljer og poeng fra resultatliste som skal fjernes.
{
	for (int  i = 1; i <= antallDeltagere; i++)  // legger de innleste deltagerne inn i arrayen.
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1] >> resultatListe[i][2]; inn.ignore();
	}
	if (ch == 'I')  // hvis den ikke er sortert, så blir den sortert.
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
	ajourfor(minusssssssss);		// oppdaterer statistikk, men sender med minus for at det skal slettes.
}

void Ovelse::skrivResultatliste()	// henter resultatliste, sorterer og skriver den til fil sortert.
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);
	ifstream inn(filnavn);
	if (inn)				// åpner resultatlista.
	{
		char sortertemp;
		inn >> sortertemp;		// leser inn enten I eller S
		inn >> antallDeltagere; inn.ignore();
		resultatListe = new float[antallDeltagere + 1][3];
		lagStatistikk(inn, sortertemp); // sendes videre til sortering.
		inn.close();		// lukker og
		remove(filnavn);	// sletter den gamle fila.
		skrivSortertResultatListe(); // lager en ny fil som er sortert.
		delete[] resultatListe;
	}
	else
	{
		cout << "\n\tResutatliste finnes ikke!" << endl;
	}
}

void Ovelse::lagStatistikk(ifstream & inn, char ch)		// sorterer og oppdaterer statistikk.
{
	for (int i = 1; i <= antallDeltagere; i++) // legger deltagere inn i memory.
	{
		inn >> resultatListe[i][0] >> resultatListe[i][1] >> resultatListe[i][2]; inn.ignore();
	}

	if (ch == 'I')	// sjekker om den trengs å sorteres.
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

	switch (resultatMetode)		// skriver ut resultatet besert på type.
	{
	case 0: skrivTid(MMSST);		break;
	case 1: skrivTid(MMSSHH);		break;
	case 2: skrivTid(MMSSTTT);	break;
	case 3: skrivPoeng(POENGX);	break;
	case 4: skrivPoeng(POENGXX);	break;
	default:
		break;
	}

	ajourfor(pluss);		// oppdatere medaljer og poeng.

}

void Ovelse::skrivSortertResultatListe()		// lager og skriver selve resultatliste fila.
{
	filtype ft = resultatliste;
	char filnavn[MAXTXT + 1] = "gruppe03/";
	lagFilNavn(filnavn, ft);		// lager filnavnet.
	ofstream utfil(filnavn);		// lager fila med det oppretta filnavnet.
	utfil << "S" << " " << antallDeltagere << endl;
	for (int m = 1; m <= antallDeltagere; m++)	// kjører gjennom hver deltager og skriver ut dataene om de.
	{
		utfil << resultatListe[m][0] << " " << resultatListe[m][1] << " " << resultatListe[m][2] << endl;
	}
}
