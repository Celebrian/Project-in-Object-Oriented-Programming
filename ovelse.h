#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include <cstring>
//Ovelse klasse deklarasjon

#include "const.h"
#include "ListTool2B.h"
#include "enum.h"

class Ovelse : public NumElement {		
private:
	char* ovelseNavn;
	int klokkeStart;
	int dato;
	int antallDeltagere;
	int deltagerListe[MAXDELTAGER][4];		//PROBABLY NOT FINAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int resultatListe[MAXDELTAGER][4];		//SAME AS THE ONE ABOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
	Ovelse(int i, char chr[]);
	void endreOvelsen();
	void endreNavn();
	void endreOvelseDato();
	void endreKlokkeslett();
	void skrivAlt();
	bool sjekkNavn(char c[]);
	bool sjekkID(int i);
	void skrivTilFil(ofstream &ut);
	Ovelse(ifstream & inn, int i);
	void lagFilNavn(int id, char ch[], filtype ft);
	void MenyOR(int id);
	void skrivMenyOR();
	void skrivResultatListe(int id);
};

#endif