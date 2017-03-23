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
	deltagerobjekt.LesDeltagereFraFil();
	grenobjekt.LesGrenerFraFil();
	poengobjekt.lesFraFil();
	Meny();
	deltagerobjekt.skrivDeltagereTilFil();
	nasjonerObjekt.skrivNasjonerTilFil();
	grenobjekt.SkrivGrenerTilFil();
	poengobjekt.skrivTilFil();
	return 0;
}