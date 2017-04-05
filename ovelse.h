#if !defined(__OVELSE_H) 
#define  __OVELSE_H

#include <cstring>
//Ovelse klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"
#include "enum.h"

class Ovelse : public NumElement {		
private:
	char* ovelseNavn;								//�velsens fulle navn
	int klokkeStart;								//Klokkeslett for starttiden til �velsen
	int dato;										//Dato �velsen foreg�r
	int antallDeltagere;							//Antall deltagere i �velsen
	int resultatMetode;
	int(*startListe)[2];							//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	float (*resultatListe)[3];						//Todimensjonal array laget p� formen i tr�den over.
	void flyttStartliste(const int i, const int j);	//Flytter "skuff" j over "skuff" i
	void nyttDynamiskArray();						//Lager nytt dynamisk array som er akkurat s� langt som det trenger � v�re

public:
	Ovelse(int i, char chr[], resultatType rt);
	Ovelse(ifstream & inn, int i, resultatType rs);	//Constructor for � lese �velse fra fil.
	void fjernOvelse();								// fjerner en �velse og sletter relaterte data.
	void lagResultat(ifstream & inn);				// lager resultat utifra deltagerliste som blir lest inn fra fil.
	void skrivTid(int in);							// skriver tiden i enten tidel, hundredel eller tusendel.
	void skrivPoeng(int t);							// skriver poeng med enten 1 eller 2 desimaler.
	int lesTid(int i, const int c);					// leser inn tid med tidel, hundredel eller tusendel.
	int lesPoeng(int i, int x);						// leser poeng med 1 eller 2 desimaler.
	void sorterResultater(char hva);				// sorterer resultater basert p� om det er tid eller poeng.
	void sorteringsProsess(int i, int j);			// selve sorteringsprosessen der ting blir flyttet p�.
	void ajourfor(plusminus oppned);				// oppdaterer poeng enten opp eller ned, sender med pluss eller minus.
	void ajourfor1(int i, plusminus oppned);		// gir f�rsteplass gull og 7 poeng.
	void ajourfor2(int i, plusminus oppned);		// gir andreplass s�lv og 5 poeng.
	void ajourfor3(int i, plusminus oppned);		// gir tredjeplass bronse og 4 poeng.
	void ajourfor4(int i, plusminus oppned);		// gir fjerdeplass 3 poeng.
	void ajourfor5(int i, plusminus oppned);		// gir femteplass 2 poeng.
	void ajourfor6(int i, plusminus oppned);		// gir sjetteplass 1 poeng.
	void endreOvelsen();							// Endre �velsemeny
	void endreNavn();								// Endre navn p� �velsen
	void endreOvelseDato();							// Endre dato for �velsen
	void endreKlokkeslett();						// Endre klokkeslett for �velsen
	void skrivAlt();								// Skriver alt om �velsen p� skjerm
	bool sjekkNavn(char c[]);						// Returnerer true hvis navnet p� �velsen matcher parameter
	bool sjekkID(int i);							// Returnerer true hvis number matcher parameter
	void skrivStartliste();							// Skriver startliste p� skjerm
	void nyStartliste();							// Lager ny startliste
	void endreStartliste();							// Viser endre startlistemeny
	void minusStartlisteDeltager();					// Fjerner en deltager fra startlisten
	void plussStartlisteDeltager();					// Legger til en ny deltager p� startlisten
	void byttStartlisteDeltager();					// Bytter en person p� startlisten med en annen
	void fjernDeltagerliste();						// Fjerner startlisten fra disk
	void skrivTilFil(ofstream &ut);					// Skriver �velse til fil
	void lagFilNavn(char ch[], filtype ft);			// Lager filnavn for start- og resultat- liste for �velse
	void MenyOR();									// Skriver menyOR
	void skrivMenyOR();								// Skriver valgmuligheter for menyOR
	void skrivMenyOLE();							// Skriver valgmuligheter for menyOLE
	void nyResultatliste();							// Lager ny resultatliste.
	void lesStartlisteFraFil(ifstream & inn);		// Leser startliste fra fil.
	void skrivStartlisteTilFil();					// Skriver startliste fra fil.
	void slettResultatListe();						// sletter resultatliste hvis den finnes.
	void slettStatistikk(ifstream & inn, char ch);  // sletter statistikken fra poeng og medaljer.
	void skrivResultatliste();						// skriver resultatliste til skjerm, etter den er blitt innlest og sortert.
	void lagStatistikk(ifstream & inn, char ch);	// oppdaterer statistikken etter resultatliste blir lest fra fil.
	void skrivSortertResultatListe();				// skriver den sorterte resultatlista til skjerm.
};

#endif