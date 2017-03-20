#include "funksjoner.h"
#include "nasjoner.h"
#include "deltagere.h"
#include "grener.h"
#include "medaljer.h"
#include "poeng.h"

Nasjoner nasjonerObjekt;
Deltagere deltagerobjekt;
Grener grenobjekt;
Medaljer medaljeobjekt;
Poeng poengobjekt;

int main() {
	nasjonerObjekt.lesNasjonerFraFil();
	Meny();
	nasjonerObjekt.skrivNasjonerTilFil();
	return 0;
}