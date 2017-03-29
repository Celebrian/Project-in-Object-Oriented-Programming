#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>

using namespace std;

#include "const.h"
#include "funksjoner.h"
#include "deltager.h"
#include "deltagere.h"
#include "nasjoner.h"
#include "grener.h"
#include "medaljer.h"
#include "poeng.h"



extern Deltagere deltagerobjekt;
extern Grener grenobjekt;
extern Nasjoner nasjonerObjekt;
extern Medaljer medaljeObjekt;
extern Poeng poengobjekt;

char les() // leser inn et ikke-blankt tegn.
{
	char ch;
	cout << "\n\nKommando:  ";
	cin >> ch;  cin.ignore();
	return (toupper(ch));
}

int les(char* t, const int min, const int max) { // leser inn et tall mellom to grenser.
	int tall;
	do {
		cout << '\t' << t << " (" << min << '-' << max << "):  ";
		cin >> tall;  cin.ignore();
	} while (tall < min || tall > max);
	return tall;
}

void les(const char t[], char s[], const int LEN) { // leser inn en ikke-blank text
	do {
		cout << '\t' << t << ": ";	cin.getline(s, LEN);
	} while (strlen(s) == 0);
}

void lesInnFraFil(char* &s, ifstream & inn)
{ // funksjon for a hente char til pointers når man leser fra fil
	char temp[MAXTXT + 1]; // lager en temp array
	do
	{
		inn.getline(temp, MAXTXT); // henter teksten fra fil
	} while (strlen(temp) == 0);
	s = new char[strlen(temp) + 1]; // lager array med spesifik storrelse
	strcpy(s, temp); // kopierer over i arrayen s
	s[strlen(temp)] = '\0'; // legger til pa slutten av s
}

int lesTelefon()
{
	char temp[MAXTXT + 1];
	int gyldigNummer;

	do
	{
		les("Skriv inn telefonnummer, ikke landskode, kun tall", temp, TELEFONNUMMER);
	} while (!kunTall(temp));			//Leser inn nummer til det er bare tall
	gyldigNummer = atoi(temp);			//Konverterer til int, siden det bare er tall
	return gyldigNummer;				//Returnerer gyldig nummer
}

void les(const char* t, char* &s) // tar med char pointer og en pointer
{	// pointeren er referanseoverfort for a ikke tulle med dens 
	// originale plass i memory.
	char temp[MAXTXT + 1]; // lager en array med max strorrelse
	do
	{
		cout << "\t" << t << ": ";
		cin.getline(temp, MAXTXT); // henter tenkst og legger den inn i temp
	} while (strlen(temp) == 0);
	s = new char[strlen(temp) + 1]; // lager array med fikset storrelse
	strcpy(s, temp); // kopierer fra temp og inn i s
	s[strlen(temp)] = '\0'; // legger inn pa slutten av arrayen.
}

void lesNasjon(const char t[], char s[], const int LEN)
{
	char temp[MAXTXT + 1];

	do {
		cout << '\t' << t << ", 3 tegn: ";
		cin.getline(temp, MAXTXT);
	} while (strlen(temp) != 3);			//Leser inn i temp helt til det er 3 tegn
	for (int i = 0; i < 3; i++)				//Går gjennom tegnene
	{
		temp[i] = toupper(temp[i]);			//Upcaser hvert tegn
	}
	strcpy(s, temp);						//Kopierer over i medsendt array
}

void skrivMeny()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Nasjon-undermeny";
	cout << "\n\tD = Deltaker-undermeny";
	cout << "\n\tG = Gren-undermeny";
	cout << "\n\tO = Ovelse-undermeny";
	cout << "\n\tM = Medaljeoversikt";
	cout << "\n\tP = Poengoversikt";
	cout << "\n\tX = eXit";
}

void Meny()
{
	char kommando;                //  Brukerens valg.
	skrivMeny();                  //  skriver ut meny med valg.

	kommando = les();             //  Leser brukerens valg.
	while (kommando != 'X') {
		switch (kommando) {
		case 'N': nasjonerObjekt.MenyN();		break;
		case 'D': deltagerobjekt.MenyD();		break;
		case 'P': poengobjekt.displayPoeng();	break;
		case 'G': grenobjekt.MenyG();			break;
		case 'O': grenobjekt.finnGren();		break;
		case 'M': medaljeObjekt.visMedaljer();	break;
		default:  skrivMeny();					break;
		}
		kommando = les();
	}
}

int lesKlokkeSlett()
{
	bool sant = true;
	char klokka[MAXTXT+1];
	int gyldigKlokka;
	do
	{
		les("\n\tLes inn klokkeslett (TTMM)", klokka, MAXTXT+1);
		if (kunTall(klokka)) 
		{
			gyldigKlokka = atoi(klokka);
			sant = false;
		}
	} while (sant || (gyldigKlokka < 0)
		|| ((gyldigKlokka / 100) > 23) || ((gyldigKlokka % 100) > 59));
	return gyldigKlokka;
}
	
int lesDato()						//LESE LOVELIG DATO
{
	bool sant = true;
	char tempdato[MAXTXT + 1];
	int dato, aaaa, mm, dd;			//Variabler for dato, dag, måned og år
	do
	{
		do
		{
			les("Skriv inn gyldig dato (p† formen: ††††mmdd) ", tempdato, MAXTXT); //Ber om gyldig dato
		} while (strlen(tempdato) == 8);
		if (kunTall(tempdato))												//På formen aaaammdd
		{
			dato = atoi(tempdato);
			aaaa = dato / 10000;					//Henter bare året fra dato
			mm = (dato / 100) % 100;				//Henter måneden fra dato
			dd = dato % 100;						//Henter dagen fra dato
			sant = false;
		}
	} while ( sant || (!finnesDato(dd, mm, aaaa)));		//Så lenge datoen ikke fins
	return dato;							//Returnerer gyldig dato
}

bool skuddaar(int aa) {    //  Sjekker om et visst år er skuddår:
						   //  Skuddår dersom: (delelig med 400) ELLER 
						   //    (delelig med 4 OG ikke med 100)
	return ((aa % 400 == 0) || ((aa % 4 == 0) && (aa % 100) != 0));
}

bool finnesDato(int da, int ma, int aa) {
	//  Setter opp antall dager i månedene.
	//   Verdien for februar settes senere.
	int dagerPrMaaned[12] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (aa < 0 || aa > 3000) return false;    //  Ulovlig år.
	if (ma < 1 || ma > 12)   return false;    //  Ulovlig måned.
											  //Ut fra om året er skuddår eller ei
	dagerPrMaaned[1] = (skuddaar(aa)) ? 29 : 28;//så settes februar verdien
	if (da < 1 || da > dagerPrMaaned[ma - 1])  return false;  // Ulovlig dag:
															  //  Garantert at er en lovlig dato!!
	return true;                          // Returnerer at datoen finnes.
}

bool kunTall(char t[])
{
	bool bareTall = true;
	int i = 0;

	while (i < strlen(t) || bareTall)
	{
		if (!isdigit(t[i]))
		{
			bareTall = false;
		}
		i++;
	}
	return true;
}

void gjorStor(char s[])
{
	bool erBokstav = true;
	int temp = strlen(s);
	for (int i = 1; i <= temp; i++)
	{
		if (!isalpha(s[i])) 
		{
			erBokstav = false;
		}
	}
	if (erBokstav) {
		for (int i = 1; i <= temp; i++)
		{
			s[i] = toupper(s[i]);
		}
	}
}

bool erLik(const char t[], const char s[])
{
	char temp[MAXTXT + 1], temp2[MAXTXT + 1];
	for (int i = 0; i <= strlen(t); i++)
	{
		temp[i] = toupper(t[i]);
	}
	for (int j = 0; j <= strlen(s); j++)
	{
		temp2[j] = toupper(s[j]);
	}
	return strcmp(temp, temp2);
}