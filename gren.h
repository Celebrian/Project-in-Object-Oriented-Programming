#if !defined(__GREN_H)
#define  GREN_H

//Gren klasse deklarasjon

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"
#include "ovelse.h"

class Gren : public TextElement {
	char* navn;								//Grenens fulle navn
	resultatType typeResultat;				//Enum som er poeng eller tid
	int antallOvelser;						//Antall �velser i denne grenen
	Ovelse* ovelser[MAXOVELSER+1];			//Array med pekere til hver �velse
public:
	Gren(char* ch);							// leser inn data fra tastatur.
	void skrivShit();
	Gren(char ch[], ifstream & inn);		// leser inn fra fil.
	void endreNyGren();						// Endrer gren
	virtual void display();					// skriver ut data
	void displayValgt();
	void SkrivGrenTilFil(ofstream & ut);	// skriver grener til fil
	void MenyO();							//Skriver menyO
	void MenyOL();							//Skriver menyOL
	void skrivMenyO();						// skriver menyen for �velse
	void skrivMenyOL();						//skriver menyen for start/deltagerliste
	void returnNavn(char t[]);				// retunerer navnet p� en nasjon til en deltager
	void nyOvelse();						// funksjon for � lage en ny �velse
	void endreOvelse();						// endrer p� en valgt �velse
	void skrivAlle();						// skriver alle data om en �velse
	void skrivOvelseTilFil(ofstream &ut);	// skriver �velsene til fil
	void lesOvelseFraFil(ifstream &inn);	// leser �velser fra fil
	void resultatListeMeny();				// meny for resultatliste
	void fjernOvelse();						// fjerner en �velse, og alle relaterte data.
};

#endif