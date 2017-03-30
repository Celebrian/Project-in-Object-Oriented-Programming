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
	int (*startListe)[2];				//http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
	int* resultatListe;

	void flyttStartliste(const int i, const int j);
	void nyttDynamiskArray();
public:
	Ovelse(int i, char chr[]);
	void endreOvelsen();
	void endreNavn();
	void endreOvelseDato();
	void endreKlokkeslett();
	void skrivAlt();
	bool sjekkNavn(char c[]);
	bool sjekkID(int i);
	void skrivStartliste();
	void nyStartliste();
	void endreStartliste();
	void minusStartlisteDeltager();
	void plussStartlisteDeltager();
	void skrivTilFil(ofstream &ut);
	Ovelse(ifstream & inn, int i);
	void lagFilNavn(char ch[], filtype ft);
	void MenyOR();
	void skrivMenyOR();
	void skrivMenyOLE();
	void skrivResultatListe();
	void nyResultatliste(int id);
	void lesStartlisteFraFil(ifstream & inn);
	void skrivStartlisteTilFil();
};

#endif