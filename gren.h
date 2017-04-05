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
	int antallOvelser;						//Antall øvelser i denne grenen
	Ovelse* ovelser[MAXOVELSER+1];			//Array med pekere til hver øvelse
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
	void skrivMenyO();						// skriver menyen for øvelse
	void skrivMenyOL();						//skriver menyen for start/deltagerliste
	void returnNavn(char t[]);				// retunerer navnet på en nasjon til en deltager
	void nyOvelse();						// funksjon for å lage en ny øvelse
	void endreOvelse();						// endrer på en valgt øvelse
	void skrivAlle();						// skriver alle data om en øvelse
	void skrivOvelseTilFil(ofstream &ut);	// skriver øvelsene til fil
	void lesOvelseFraFil(ifstream &inn);	// leser øvelser fra fil
	void resultatListeMeny();				// meny for resultatliste
	void fjernOvelse();						// fjerner en øvelse, og alle relaterte data.
};

#endif