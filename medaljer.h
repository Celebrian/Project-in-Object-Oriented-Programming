#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

//Medaljer klasse deklarasjon

#include "enum.h"
#include "statestikk.h"
#include "ListTool2B.h"

class Medaljer : public Statestikk {
private:
	int medaljeListe[MAXNASJONER][3];				//Antall gull, sølv og bronse medaljer

	void bytt(const int i, const int j);			//Flytter Nasjoner i arrayene
public:
	void nyMedalje(const char land[LANDSKODE], const medalje pris);
	void sorterMedaljer();							//Sorterer medaljer
	void visMedaljer();						//TEST FUNKSJON
	void lesMedaljerFraFil();						//Les medaljer fra fil
	void skrivMedaljerTilFil();						//Skriv medaljer til fil
};

#endif