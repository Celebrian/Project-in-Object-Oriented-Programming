#if !defined(__STATESTIKK_H)
#define  __STATESTIKK_H

#include <fstream>
using namespace std;

//Statestikk klasse deklarasjon

#include "const.h"

class Statestikk {
private:
protected:
	char nasjonForkortelser[MAXNASJONER + 1][LANDSKODE];	//Array med landskoder
	int sisteBrukt;											//Antall nasjoner lagt inn i lista med minst en medalje
public:
	virtual void lesFraFil(ifstream & inn, int t);			//Leser statestikk fra fil
	virtual void skrivTilFil(ofstream & ut);				//Skriver statestikk til fil

};

#endif