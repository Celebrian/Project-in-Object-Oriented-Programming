#if !defined(__DELTAGER_H) 
#define  __DELTAGER_H

//Deltager klasse deklarasjon

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"

class Deltager : public NumElement {
private:
	char* navn;	
	char nasjon[LANDSKODE + 1];		// Tre bokstaver
	kjonn gender;		// enum med gutt/jente
	char andreData[MAXTXT + 1];
public:
	Deltager(int n, char chr[]);	// kjøres når en ny deltager opprettes
	Deltager(int n, ifstream & inn);
	void endreNyDeltager();	// for å endre en deltager besert på nummer innskrevet
	virtual void display();	// skriver ut data
	void displayAll();	// skriver ut alle data
	void skrivDeltagerID();
	bool sjekkLand(char ch[LANDSKODE]);	// sjekker om en nasjon finnes
	void skrivDeltagerTilFil(ofstream & ut);
	void lesInnNasjon(char ch[]); // sjekker at en nasjon finnes før den faktisk oppdateres
	void endreDeltagersNasjon(char ch[]); // endrer nasjonen til valgt deltager
	void endreNavn();	// sletter først også leser inn nytt navn på valgt deltager
	void endreKjonn();	// endrer kjønnet på valgt deltager
	void endreAndreData(); // endrer andre data.
	void startSkriv();	// skriver startnummeret til en deltager
	void hentNasjon(char chr[]);	// retunerer nasjonen til en deltager
};


#endif