#if !defined(__DELTAGERE_H)
#define  __DELTAGERE_H

//Deltagere klasse deklarasjon

#include "ListTool2B.h"

class Deltagere {
private: 
	List* deltagerListe;
	int sisteDeltager;
public:
	Deltagere();
	void lagNyDeltager();
	void endreDeltager();
	void skrivUt();
	void skrivUtValgt();
};

#endif