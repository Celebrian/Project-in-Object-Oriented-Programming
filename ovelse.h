#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include <cstring>
//Ovelse klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"
#include "enum.h"

class Ovelse : public NumElement {		
private:
	char* ovelseNavn;					//Øvelsens fulle navn
	int klokkeStart;					//Klokkeslett for starttiden til øvelsen
	int dato;							//Dato øvelsen foregår
	int antallDeltagere;				//Antall deltagere i øvelsen
	int resultatMetode;
	int(*startListe)[2];				//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	float (*resultatListe)[3];			//Todimensjonal array laget på formen i tråden over.
	void flyttStartliste(const int i, const int j);//Flytter "skuff" j over "skuff" i
	void nyttDynamiskArray();			//Lager nytt dynamisk array som er akkurat så langt som det trenger å være

public:
	Ovelse(int i, char chr[], resultatType rt);
	Ovelse(ifstream & inn, int i, resultatType rs);	//Constructor for å lese øvelse fra fil
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
	void endreOvelsen();				//Endre øvelsemeny
	void endreNavn();					//Endre navn på øvelsen
	void endreOvelseDato();				//Endre dato for øvelsen
	void endreKlokkeslett();			//Endre klokkeslett for øvelsen
	void skrivAlt();					//Skriver alt om øvelsen på skjerm
	bool sjekkNavn(char c[]);			//Returnerer true hvis navnet på øvelsen matcher parameter
	bool sjekkID(int i);				//Returnerer true hvis number matcher parameter
	void skrivStartliste();				//Skriver startliste på skjerm
	void nyStartliste();				//Lager ny startliste
	void endreStartliste();				//Viser endre startlistemeny
	void minusStartlisteDeltager();		//Fjerner en deltager fra startlisten
	void plussStartlisteDeltager();		//Legger til en ny deltager på startlisten
	void byttStartlisteDeltager();		//Bytter en person på startlisten med en annen
	void fjernDeltagerliste();			//Fjerner startlisten fra disk
	void skrivTilFil(ofstream &ut);		//Skriver øvelse til fil
	void lagFilNavn(char ch[], filtype ft);//Lager filnavn for start- og resultat- liste for øvelse
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