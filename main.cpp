#include "funksjoner.h"
#include "nasjoner.h"
#include "deltagere.h"
#include "grener.h"
#include "medaljer.h"
#include "poeng.h"

Nasjoner nasjonerObjekt;
Deltagere deltagerobjekt;
Grener grenobjekt;
Medaljer medaljeObjekt;
Poeng poengobjekt;

int main() {
	nasjonerObjekt.lesNasjonerFraFil();
	deltagerobjekt.LesDeltagereFraFil();
	grenobjekt.LesGrenerFraFil();
	Meny();
	deltagerobjekt.skrivDeltagereTilFil();
	nasjonerObjekt.skrivNasjonerTilFil();
	grenobjekt.SkrivGrenerTilFil();
	return 0;
}
