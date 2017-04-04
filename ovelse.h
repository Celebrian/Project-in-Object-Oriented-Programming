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
	int resultatMetode;
	int(*startListe)[2];				//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	float (*resultatListe)[3];			//Todimensjonal array laget p� formen i tr�den over.
	void flyttStartliste(const int i, const int j);//Flytter "skuff" j over "skuff" i
	void nyttDynamiskArray();			//Lager nytt dynamisk array som er akkurat s� langt som det trenger � v�re

public:
	Ovelse(int i, char chr[], resultatType rt);
	Ovelse(ifstream & inn, int i, resultatType rs);	//Constructor for � lese �velse fra fil
	void lagResultat(ifstream & inn);
	void skrivTid(int in);
	void skrivPoeng(int t);
	void lesTid(int i, const int c);
	void lesPoeng(int i, int x);
	void sorterResultater(char hva);
	void sorteringsProsess(int i, int j);
	void ajourfor();
	void ajourfor1(int i, plusminus oppned);
	void ajourfor2(int i, plusminus oppned);
	void ajourfor3(int i, plusminus oppned);
	void ajourfor4(int i, plusminus oppned);
	void ajourfor5(int i, plusminus oppned);
	void ajourfor6(int i, plusminus oppned);
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
	void lagFilNavn(char ch[], filtype ft);//Lager filnavn for start- og resultat- liste for �velse
	void MenyOR();						//Skriver menyOR
	void skrivMenyOR();					//Skriver valgmuligheter for menyOR
	void skrivMenyOLE();				//Skriver valgmuligheter for menyOLE
	void nyResultatliste();				//Lager ny resultatliste
	void lesStartlisteFraFil(ifstream & inn);//Leser startliste fra fil
	void skrivStartlisteTilFil();		//Skriver startliste fra fil
	void slettResultatListe();
	void slettStatistikk(ifstream & inn, char ch);
};

#endif