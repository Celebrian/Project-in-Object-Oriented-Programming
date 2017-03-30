#if !defined(__DELTAGERE_H)
#define  __DELTAGERE_H

//Deltagere klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"

class Deltagere {
private: 
	List* deltagerListe;
	int sisteDeltager;
public:
	Deltagere();
	void lagNyDeltager(); // lager ny deltager.
	void endreDeltager();	// endrer valgte data om en deltager.
	void skrivUt();	// skriver ut noen data om alle objekter.
	void skrivUtValgt();	// skriver ut valge data om valgt objekt.
	void loopGjennom(char ch[LANDSKODE+1]); // sjekker om en nasjon finnes.
	void MenyD();	// lager en meny.
	void skrivMenyD();	// skriver menyvalg.
	void skrivID(const int id);
	bool finnesID(const int id);
	int antallDeltagere();
	void LesDeltagereFraFil(); 
	void skrivDeltagereTilFil();
};

#endif