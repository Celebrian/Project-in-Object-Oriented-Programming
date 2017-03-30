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
	void sorterMedaljer();							//Sorterer medaljer
public:
	void endreMedalje(const char land[LANDSKODE], const medalje pris, const plusminus increment);
	void visMedaljer();								//Skriver medaljer til skjerm
	void lesMedaljerFraFil();						//Les medaljer fra fil
	void skrivMedaljerTilFil();						//Skriv medaljer til fil
};

#endif