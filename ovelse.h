#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include <cstring>
//Ovelse klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"
#include "enum.h"

class Ovelse : public NumElement {		
private:
	char* ovelseNavn;					//�velsens fulle navn
	int klokkeStart;					//Klokkeslett for starttiden til �velsen
	int dato;							//Dato �velsen foreg�r
	int antallDeltagere;				//Antall deltagere i �velsen
	int (*startListe)[2];				//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	int* resultatListe;

	void flyttStartliste(const int i, const int j);//Flytter "skuff" j over "skuff" i
	void nyttDynamiskArray();			//Lager nytt dynamisk array som er akkurat s� langt som det trenger � v�re
public:
	Ovelse(int i, char chr[]);			//Constructor leser inn data for ny �velse
	void endreOvelsen();				//Endre �velsemeny
	void endreNavn();					//Endre navn p� �velsen
	void endreOvelseDato();				//Endre dato for �velsen
	void endreKlokkeslett();			//Endre klokkeslett for �velsen
	void skrivAlt();					//Skriver alt om �velsen p� skjerm
	bool sjekkNavn(char c[]);			//Returnerer true hvis navnet p� �velsen matcher parameter
	bool sjekkID(int i);				//Returnerer true hvis number matcher parameter
	void skrivStartliste();				//Skriver startliste p� skjerm
	void nyStartliste();				//Lager ny startliste
	void endreStartliste();				//Viser endre startlistemeny
	void minusStartlisteDeltager();		//Fjerner en deltager fra startlisten
	void plussStartlisteDeltager();		//Legger til en ny deltager p� startlisten
	void byttStartlisteDeltager();		//Bytter en person p� startlisten med en annen
	void fjernDeltagerliste();			//Fjerner startlisten fra disk
	void skrivTilFil(ofstream &ut);		//Skriver �velse til fil
	Ovelse(ifstream & inn, int i);		//Constructor for � lese �velse fra fil
	void lagFilNavn(char ch[], filtype ft);//Lager filnavn for start- og resultat- liste for �velse
	void MenyOR();						//Skriver menyOR
	void skrivMenyOR();					//Skriver valgmuligheter for menyOR
	void skrivMenyOLE();				//Skriver valgmuligheter for menyOLE
	void skrivResultatListe();			//Skriver resultatliste p� skjerm
	void nyResultatliste(int id);		//Lager ny resultatliste
	void lesStartlisteFraFil(ifstream & inn);//Leser startliste fra fil
	void skrivStartlisteTilFil();		//Skriver startliste fra fil
};

#endif