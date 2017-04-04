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
public:
	Deltager(int n, char chr[]);	// kj�res n�r en ny deltager opprettes
	Deltager(int n, ifstream & inn);
	void endreNyDeltager();	// for � endre en deltager besert p� nummer innskrevet
	virtual void display();	// skriver ut data
	void displayAll();	// skriver ut alle data
	void skrivDeltagerID();
	bool sjekkLand(char ch[LANDSKODE]);	// sjekker om en nasjon finnes
	void skrivDeltagerTilFil(ofstream & ut);
	void lesInnNasjon(char ch[]); // sjekker at en nasjon finnes f�r den faktisk oppdateres
	void endreDeltagersNasjon(char ch[]);
	void endreNavn();
	void endreKjonn();
	void startSkriv();
	void hentNasjon(char chr[]);
};


#endif