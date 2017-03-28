#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>

using namespace std;

#include "funksjoner.h"
#include "ovelse.h"

Ovelse::Ovelse(int i, char chr[]) : NumElement(i)
{
	navn = new char[strlen(chr) + 1];			
	strcpy(navn, chr);	
	klokkeStart = lesKlokkeSlett();
	dato = lesDato();
	antallDeltagere = 0;
}

bool Ovelse::sjekkNavn(char c[])
{
	return(!strcmp(c, navn));
}

bool Ovelse::sjekkID(int i)
{
	return(i == number);
}
