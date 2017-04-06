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

	if (nasjonerObjekt.lesNasjonerFraFil())		// sjekker om nasjoner blir lest inn, fordi resten av programmet er avhengig av nasjoner for å fungere riktig.
	{
		deltagerobjekt.LesDeltagereFraFil();
		grenobjekt.LesGrenerFraFil();
		medaljeObjekt.lesMedaljerFraFil();
		poengobjekt.lesFraFil();
	}
	else
	{
		cout << "\t\nError: noe var galt med en eller flere av filene." << endl << endl;
	}
	
	Meny();
	deltagerobjekt.skrivDeltagereTilFil();
	nasjonerObjekt.skrivNasjonerTilFil();
	grenobjekt.SkrivGrenerTilFil();
	medaljeObjekt.skrivMedaljerTilFil();
	poengobjekt.skrivTilFil();
	return 0;
}
