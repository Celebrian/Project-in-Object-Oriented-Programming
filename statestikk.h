#if !defined(__STATESTIKK_H)
#define  __STATESTIKK_H

//Statestikk klasse deklarasjon

#include "const.h"

class Statestikk {
private:
protected:
	char nasjonForkortelser[MAXNASJONER + 1][LANDSKODE];
	int sisteBrukt;									//Antall nasjoner lagt inn i lista med minst en medalje
public:

};

#endif