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
	deltagerobjekt.LesDeltagereFraFil();
	nasjonerObjekt.lesNasjonerFraFil();
	Meny();
	nasjonerObjekt.skrivNasjonerTilFil();
	deltagerobjekt.skrivDeltagereTilFil();
	return 0;
}