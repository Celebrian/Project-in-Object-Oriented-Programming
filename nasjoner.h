#if !defined(NASJONER_H)
#define  NASJONER_H

//Nasjoner klasse deklarasjon

#include "ListTool2B.h"

class Nasjoner {
private:
	List* nasjonListe;					//Liste over nasjoner
public:
	Nasjoner();							//Construktor
	void skrivMenyN();					//Skriver undermeny N
	void MenyN();						//Undermeny N
	void registrerNasjon();				//Registrerer ny nasjon
	void endreNasjon();					//Endrer data ved en nasjon
	void skrivAlleNasjoner();			//Skriver alle nasjoner med displaylist
	void skrivNasjonDeltagere();		//Skriver alle deltagere ved en nasjon
	void skrivEnNasjon();				//Skriver all informasjon om en nasjon
	bool finnesNasjon(const char t[]);	//Skjekker om nasjon finnes
	void plussDeltager(const char t[]);	//Legger til en deltager
	void minusDeltager(const char t[]);	//Trekker fra en deltager
	void lesNasjonerFraFil();			//Leser Nasjoner fra fil
	void skrivNasjonerTilFil();			//Skriver nasjoner til fil
};


#endif