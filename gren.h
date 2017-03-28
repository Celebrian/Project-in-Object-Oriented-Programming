#if !defined(__GREN_H)
#define  GREN_H

//Gren klasse deklarasjon

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"
#include "ovelse.h"

class Gren : public TextElement {
	char* navn;
	resultatType typeResultat;
	int antallOvelser;
	Ovelse* ovelser[MAXOVELSER+1];
public:
	Gren(char* ch);							// leser inn data fra tastatur.
	Gren(char ch[], ifstream & inn);		// leser inn fra fil.
	void endreNyGren();						// Endrer gren
	virtual void display();					// skriver ut data
	void displayValgt();
	void SkrivGrenTilFil(ofstream & ut);	// skriver grener til fil
	void MenyO();
	//void MenyOL();
	//void MenyOR();
	void skrivMenyO();
	void skrivMenyOL();
	void skrivMenyOR();
	void returnNavn(char t[]);
	void nyOvelse();
	void endreOvelse();
	void skrivAlle();
};

#endif