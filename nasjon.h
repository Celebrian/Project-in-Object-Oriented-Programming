#if !defined(__NASJON_H)
#define __NASJON_H

//Nasjon klasse deklarasjon
#include <fstream>

#include "deltagere.h"
#include "ListTool2B.h"

extern Deltagere deltagerobjekt;

class Nasjon : public TextElement {
private:								//text = nasjonsforkortelse
	char* navn;							//Nasjonsnavn
	int antallDeltagere;				//Antall Deltagere
	char* kontaktNavn;					//Navn på kontaktperson
	int kontaktTelefon;					//Telefon til kontaktperson
public:
	Nasjon(char* landskode);			//Construktor for ny nasjon
	Nasjon(ifstream & inn, char* landskode);//Construktor for ny nasjon fra fil
	void endreNasjon();					//Endre data om nasjon
	void endreNasjonNavn();				//Endre navn på nasjon
	void endreKontaktNavn();			//Endre navn på kontaktperson
	void endreTelefon();				//Endre telefon på kontaktperson
	virtual void display();				//Vise info om nasjon
	void displayAlt();					//Vise all info om nasjon
	void pluss();						//Teller opp antall deltagere
	void minus();						//Teller ned antall deltagere
	void skrivNasjonTilFil(ofstream & ut);	//Skrive nasjon til fil
};

#endif