#if !defined(__POENG_H)
#define  __POENG_H

//Poeng klasse deklarasjon

#include "statestikk.h"
#include "ListTool2B.h"
#include "enum.h"

class Poeng : public Statestikk {
private: 
	int poengOversikt[MAXNASJONER];		// array med oversikt over hver nasjon sine poeng
public:
	void oppdaterPoeng(char ch[LANDSKODE], int antP, plusminus oppellerned); // legger enten til eller trekker fra poeng.
	void sorterPoeng();														// sorterer nasjonene utifra hvor mye poeng de har.
	void displayPoeng();													// skriver poengene til hver nasjon på skjerm.
	void lesFraFil();														// leser poeng fra fil
	void skrivTilFil();														// skriver poeng til fil
};




#endif