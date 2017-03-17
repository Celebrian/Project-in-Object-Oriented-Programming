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
	void lagNyDeltager();
	void endreDeltager();
	void skrivUt();
	void skrivUtValgt();
	void loopGjennom(char ch[LANDSKODE+1]);
};

#endif