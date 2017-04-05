#include "funksjoner.h"
#include "nasjoner.h"
#include "deltagere.h"
#include "grener.h"
#include "medaljer.h"
#include "poeng.h"

#include <iostream>

Nasjoner nasjonerObjekt;
Deltagere deltagerobjekt;
Grener grenobjekt;
Medaljer medaljeObjekt;
Poeng poengobjekt;

int main() {

	nasjonerObjekt.lesNasjonerFraFil();
	deltagerobjekt.LesDeltagereFraFil();
	grenobjekt.LesGrenerFraFil();
	grenobjekt.lesOvelserFraFil();
	medaljeObjekt.lesMedaljerFraFil();
	poengobjekt.lesFraFil();
	Meny();
	deltagerobjekt.skrivDeltagereTilFil();
	nasjonerObjekt.skrivNasjonerTilFil();
	grenobjekt.SkrivGrenerTilFil();
	medaljeObjekt.skrivMedaljerTilFil();
	poengobjekt.skrivTilFil();
	grenobjekt.skrivOvelserTilFil();
	return 0;
}
