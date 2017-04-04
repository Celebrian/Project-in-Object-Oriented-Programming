#if !defined(__POENG_H)
#define  __POENG_H

//Poeng klasse deklarasjon

#include "statestikk.h"
#include "ListTool2B.h"
#include "enum.h"

class Poeng : public Statestikk {
private: 
	int poengOversikt[MAXNASJONER];
public:
	void oppdaterPoeng(char ch[LANDSKODE], int antP, plusminus oppellerned);
	void sorterPoeng();
	void displayPoeng();
	void lesFraFil();
	void skrivTilFil();
};




#endif