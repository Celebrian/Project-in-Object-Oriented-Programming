#if !defined(NASJONER_H)
#define  NASJONER_H

//Nasjoner klasse deklarasjon

#include "ListTool2B.h"

class Nasjoner {
private:
	List* nasjonListe;
public:
	Nasjoner();
	void skrivMenyN();
	void MenyN();
	void registrerNasjon();
	void endreNasjon();
	void skrivNasjonDeltagere();
	void skrivEnNasjon();
};


#endif