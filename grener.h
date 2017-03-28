#if !defined(__GRENER_H)
#define  __GRENER_H

//Grener klasse deklarasjon

#include "ListTool2B.h"

class Grener {
private:
	List* grenListe;
	int sisteGren; // HUSK
public:
	Grener();
	void lagNyGren();
	void endreGren();
	void skrivUt();
	void skrivUtValgt();
	void MenyG();
	void skrivMenyG();
	void finnGren();
	void LesGrenerFraFil();
	void SkrivGrenerTilFil();
	void skrivOvelserTilFil();
	void lesOvelserFraFil();
};
#endif