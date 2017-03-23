#if !defined(__POENG_H)
#define  __POENG_H

//Poeng klasse deklarasjon

#include "statestikk.h"
#include "ListTool2B.h"

class Poeng : public Statestikk {
private: 
	int poengOversikt[MAXNASJONER];
public:
	void oppdaterPoeng(char ch[LANDSKODE], int antP);
	void sorterPoeng();
	void displayPoeng();
};




#endif