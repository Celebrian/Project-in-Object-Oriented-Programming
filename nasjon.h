#if !defined(__NASJON_H)
#define __NASJON_H

//Nasjon klasse deklarasjon
#include <fstream>

#include "ListTool2B.h"

class Nasjon : public TextElement {
private:								//text = nasjonsforkortelse
	char* navn;							//Nasjonsnavn
	int antallDeltagere;				//Antall Deltagere
	char* kontaktNavn;					//Navn på kontaktperson
	int kontaktTelefon;					//Telefon til kontaktperson
	char* annet;						//Annen informasjon

	void endreNasjonNavn();				//Endre navn på nasjon
	void endreKontaktNavn();			//Endre navn på kontaktperson
	void endreTelefon();				//Endre telefon på kontaktperson
	void endreAnnet();					//Endre annen informasjon om nasjonen
public:
	Nasjon(char* landskode);			//Construktor for ny nasjon
	Nasjon(ifstream & inn, char* landskode);	//Construktor for ny nasjon fra fil
	void skrivMenyNE();					//Skriver endre nasjon meny
	void endreNasjon();					//Endre data om nasjon
	virtual void display();				//Vise info om nasjon
	void displayAlt();					//Vise all info om nasjon
	void plussDeltager();						//Teller opp antall deltagere
	void minusDeltager();						//Teller ned antall deltagere
	void skrivNasjonTilFil(ofstream & ut);	//Skrive nasjon til fil
};

#endif