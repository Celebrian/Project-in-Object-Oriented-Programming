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
	int resultatMetode;
	int deltagerListe[MAXDELTAGER][4];		//PROBABLY NOT FINAL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	float (*resultatListe)[3];		//SAME AS THE ONE ABOVE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
public:
	Ovelse(int i, char chr[], resultatType rt);
	void endreOvelsen();
	void endreNavn();
	void endreOvelseDato();
	void endreKlokkeslett();
	void skrivAlt();
	bool sjekkNavn(char c[]);
	bool sjekkID(int i);
	void skrivDeltagerListe(const int id);
	void skrivTilFil(ofstream &ut);
	Ovelse(ifstream & inn, int i, resultatType rs);
	void lagFilNavn(int id, char ch[], filtype ft);
	void MenyOR(int id);
	void skrivMenyOR();
	void skrivResultatListe(int id);
	void nyResultatliste(int id);
	void lagResultat(ifstream & inn);
	void skrivTid(int in);
	void skrivPoeng(int t);
	void lesTid(int i, const int c);
	void lesPoeng(int i, int x);
	void sorterResultater(char hva);
	void sorteringsProsess(int i, int j);
	void ajourfor();
	void ajourfor1(int i);
	void ajourfor2(int i);
	void ajourfor3(int i);
	void ajourfor4(int i);
	void ajourfor5(int i);
	void ajourfor6(int i);
};

#endif