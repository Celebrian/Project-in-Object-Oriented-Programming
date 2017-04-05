#if !defined(__OVELSE_H) 
#define  __OVELSE_H

#include <cstring>
//Ovelse klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"
#include "enum.h"

class Ovelse : public NumElement {		
private:
	char* ovelseNavn;								//Øvelsens fulle navn
	int klokkeStart;								//Klokkeslett for starttiden til øvelsen
	int dato;										//Dato øvelsen foregår
	int antallDeltagere;							//Antall deltagere i øvelsen
	int resultatMetode;
	int(*startListe)[2];							//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	float (*resultatListe)[3];						//Todimensjonal array laget på formen i tråden over.
	void flyttStartliste(const int i, const int j);	//Flytter "skuff" j over "skuff" i
	void nyttDynamiskArray();						//Lager nytt dynamisk array som er akkurat så langt som det trenger å være

public:
	Ovelse(int i, char chr[], resultatType rt);
	Ovelse(ifstream & inn, int i, resultatType rs);	//Constructor for å lese øvelse fra fil.
	void fjernOvelse();								// fjerner en øvelse og sletter relaterte data.
	void lagResultat(ifstream & inn);				// lager resultat utifra deltagerliste som blir lest inn fra fil.
	void skrivTid(int in);							// skriver tiden i enten tidel, hundredel eller tusendel.
	void skrivPoeng(int t);							// skriver poeng med enten 1 eller 2 desimaler.
	int lesTid(int i, const int c);					// leser inn tid med tidel, hundredel eller tusendel.
	int lesPoeng(int i, int x);						// leser poeng med 1 eller 2 desimaler.
	void sorterResultater(char hva);				// sorterer resultater basert på om det er tid eller poeng.
	void sorteringsProsess(int i, int j);			// selve sorteringsprosessen der ting blir flyttet på.
	void ajourfor(plusminus oppned);				// oppdaterer poeng enten opp eller ned, sender med pluss eller minus.
	void ajourfor1(int i, plusminus oppned);		// gir førsteplass gull og 7 poeng.
	void ajourfor2(int i, plusminus oppned);		// gir andreplass sølv og 5 poeng.
	void ajourfor3(int i, plusminus oppned);		// gir tredjeplass bronse og 4 poeng.
	void ajourfor4(int i, plusminus oppned);		// gir fjerdeplass 3 poeng.
	void ajourfor5(int i, plusminus oppned);		// gir femteplass 2 poeng.
	void ajourfor6(int i, plusminus oppned);		// gir sjetteplass 1 poeng.
	void endreOvelsen();							// Endre øvelsemeny
	void endreNavn();								// Endre navn på øvelsen
	void endreOvelseDato();							// Endre dato for øvelsen
	void endreKlokkeslett();						// Endre klokkeslett for øvelsen
	void skrivAlt();								// Skriver alt om øvelsen på skjerm
	bool sjekkNavn(char c[]);						// Returnerer true hvis navnet på øvelsen matcher parameter
	bool sjekkID(int i);							// Returnerer true hvis number matcher parameter
	void skrivStartliste();							// Skriver startliste på skjerm
	void nyStartliste();							// Lager ny startliste
	void endreStartliste();							// Viser endre startlistemeny
	void minusStartlisteDeltager();					// Fjerner en deltager fra startlisten
	void plussStartlisteDeltager();					// Legger til en ny deltager på startlisten
	void byttStartlisteDeltager();					// Bytter en person på startlisten med en annen
	void fjernDeltagerliste();						// Fjerner startlisten fra disk
	void skrivTilFil(ofstream &ut);					// Skriver øvelse til fil
	void lagFilNavn(char ch[], filtype ft);			// Lager filnavn for start- og resultat- liste for øvelse
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