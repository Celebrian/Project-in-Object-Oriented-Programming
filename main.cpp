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
	medaljeObjekt.lesMedaljerFraFil();
	poengobjekt.lesFraFil();
	Meny();
	deltagerobjekt.skrivDeltagereTilFil();
	nasjonerObjekt.skrivNasjonerTilFil();
	grenobjekt.SkrivGrenerTilFil();
	medaljeObjekt.skrivMedaljerTilFil();
	poengobjekt.skrivTilFil();
	return 0;
}
