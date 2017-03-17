#if !defined(__NASJON_H)
#define __NASJON_H

//Nasjon klasse deklarasjon

#include "deltagere.h"
#include "ListTool2B.h"

extern Deltagere deltagerobjekt;

class Nasjon : public TextElement {
private:
	char* navn;
	int antallDeltagere;
	char* kontaktNavn;
	int kontaktTelefon;
public:
	Nasjon(char* landskode);
	void endreNasjon();
	void endreNasjonNavn();
	void endreKontaktNavn();
	void endreTelefon();
	virtual void display();
	void displayAlt();
};

#endif