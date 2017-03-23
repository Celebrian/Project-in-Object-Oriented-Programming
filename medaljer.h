#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

//Medaljer klasse deklarasjon

#include "enum.h"
#include "statestikk.h"
#include "ListTool2B.h"

class Medaljer : public Statestikk {
private:
	int medaljeliste[MAXNASJONER][3];				//Antall gull, sølv og bronse medaljer
	int sisteBrukt;									//
public:
	void nyMedalje(const char land[], const medalje pris);
};

#endif