#if !defined(NASJONER_H)
#define  NASJONER_H

//Nasjoner klasse deklarasjon

#include "ListTool2B.h"
#include "funksjoner.h"
#include "const.h"

class Nasjoner {
private:
	List* nasjonListe;
public:
	Nasjoner();
	void skrivMenyN();
	void MenyN();
	void registrerNasjon();
	void endreNasjon();

	void skrivEnNasjon();
};


#endif