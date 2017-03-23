#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

//Medaljer klasse deklarasjon

#include "enum.h"
#include "statestikk.h"
#include "ListTool2B.h"

class Medaljer : public Statestikk {
private:
	int medaljeListe[MAXNASJONER][3];				//Antall gull, sølv og bronse medaljer
public:
	void nyMedalje(const char land[LANDSKODE], const medalje pris);
	void sorterMedaljer();							//Bubblesort medaljer
	void flytt(const int i, const int j);
	void visMedaljer();
};

#endif