#if !defined(__STATESTIKK_H)
#define  __STATESTIKK_H

#include <fstream>
using namespace std;

//Statestikk klasse deklarasjon

#include "const.h"

class Statestikk {
private:
protected:
	char nasjonForkortelser[MAXNASJONER][LANDSKODE];
	int sisteBrukt;
public:
	virtual void lesFraFil(ifstream & inn, int t);
	virtual void skrivTilFil(ofstream & ut);

};

#endif