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
	char temp[MAXTXT + 1];
	char ch;
	cout << "\n\nKommando:  ";
	cin >> ch; cin.getline(temp, MAXTXT);
	return (toupper(ch));
}

int les(char* t, const int min, const int max) { // leser inn et tall mellom to grenser.
	bool erTall = false;						//Regner med at det ikke er tall
	char tall[MAXTXT + 1];
	int faktiskTall;
	do {
		cout << '\t' << t << " (" << min << '-' << max << "):  ";
		cin.getline(tall, MAXTXT);
		if (kunTall(tall))						//Skjekker om det faktisk er bare tall
		{
			faktiskTall = atoi(tall);			//Gjør om dersom det er bare tall
			erTall = true;						//Setter at det er tall
		}										//Looper mens det ikke er et tall mellom min og max
	} while (!erTall || faktiskTall < min || faktiskTall > max);
	return faktiskTall;							//Returnerer faktisk tall
}	

void les(const char t[], char s[], const int LEN) { // leser inn en ikke-blank text
	do {
		cout << '\t' << t << ": ";	cin.getline(s, LEN);
		fjernBlanke(s);
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
		fjernBlanke(temp);
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
		default:								break;
		}
		skrivMeny();
		kommando = les();
	}
}

int lesKlokkeSlett()
{
	bool sant = true; // flagg
	char klokka[MAXTXT+1]; 
	int gyldigKlokka;
	do
	{
		les("\n\tLes inn klokkeslett (TTMM)", klokka, MAXTXT + 1); // leser inn i et char array.
		if (kunTall(klokka))	//sjekker om teksten består av bare tall.
		{
			gyldigKlokka = atoi(klokka); // konverterer fra char til int met atoi.
			sant = false;
		}
	} while (sant || (gyldigKlokka < 0)									//sjekker at det som er innlest
		|| ((gyldigKlokka / 100) > 23) || ((gyldigKlokka % 100) > 59));	// er et gyldig klokkeslett.
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
		} while (strlen(tempdato) != 8);
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
	if (aa < MINAAR || aa > MAXAAR) return false;    //  Ulovlig år.
	if (ma < 1 || ma > 12)   return false;    //  Ulovlig måned.
											  //Ut fra om året er skuddår eller ei
	dagerPrMaaned[1] = (skuddaar(aa)) ? 29 : 28;//så settes februar verdien
	if (da < 1 || da > dagerPrMaaned[ma - 1])  return false;  // Ulovlig dag:
															  //  Garantert at er en lovlig dato!!
	return true;                          // Returnerer at datoen finnes.
}

bool kunTall(char t[]) // sjekker om en int bare er tall.
{
	int i = 0;

	while (i < strlen(t)) // kjører helt til arrayet et slutt.
	{
		if (!isdigit(t[i])) // sjekker om hver skuff er en tall, med isdigit funksjon.
		{
			return false; // returnerer false hvis den finner en bokstav.
		}
		i++;
	}
	return true;	// ellers retunerer true.
}

bool kunTallFloat(char t[])  // samme som funksjonen ovenfor, men her tar den en float istedet for int.
{
	int i = 0;

	while (i < strlen(t)) // kjører helt til arrayet et slutt.
	{
		if (!((isdigit(t[i])) || ( t[i] == '.'))) // sjekker om hver skuff er en tall, med isdigit funksjon.
		{
			return false; // returnerer false hvis den finner en bokstav.
		}
		i++;
	}
	return true;	// ellers retunerer true.
}

void gjorStor(char s[]) // tar en array og gjør alle bokstavene store.
{
	bool erBokstav = true;
	int temp = strlen(s);
	for (int i = 0; i < temp; i++)
	{
		if (!isalpha(s[i]))  // sjekker om det er en bokstav med isalpha.
		{
			erBokstav = false; // returnerer false om det er et tall.
		}
	}
	if (erBokstav) {			//hvis det bare var bokstaver.
		for (int i = 0; i < temp; i++) // kjører gjennom alle,
		{
			s[i] = toupper(s[i]);	// gjør alle til uppercase.
		}
	}
}

bool erLik(const char t[], const char s[]) //sjekker om to tekster er like.
{
	char temp[MAXTXT + 1], temp2[MAXTXT + 1];
	for (int i = 0; i <= strlen(t); i++) // går gjennom begge tekstene
	{
		if (isalpha(t[i]))				//Hvis det er snakk om bokstaver
		{
			temp[i] = toupper(t[i]);	//Gjør de uppercase
		}
		else if (isdigit(t[i]))			//Hvis det er snakk om tall
		{
			temp[i] = t[i];				//Legg tallet slik det er over
		}
		else if (t[i] == '-' || t[i] == '.' || t[i] == '\0' || t[i] == ' ')	//Hvis det er snakk om - eller .
		{
			temp[i] = t[i];				//Bare legg det over
		}
		else return false;			//Hvis det ikke er noe av det over, bare si de ikke er like(PGA ulovlige tegn)
	}
	for (int j = 0; j <= strlen(s); j++)	//Samme for den andre arrayen
	{
		if (isalpha(s[j]))
		{
			temp2[j] = toupper(s[j]);
		}
		else if (isdigit(s[j]))
		{
			temp2[j] = s[j];
		}
		else if (s[j] == '-' || s[j] == '.' || s[j] == '\0' || s[j] == ' ')
		{
			temp2[j] = s[j];
		}
		else return false;	
	}
	return !strcmp(temp, temp2);		//Returnerer true (1) hvis like
}

void fjernBlanke(char t[])			// stripper tekster av blanke foran og bak.
{
	int lengde = strlen(t), bokstaverForran = 0, bokstaverBak = 0, i = 0, l = 0;
	bool bokstav = false;
	char temp[MAXTXT + 1];
	while (!(bokstav && i <=lengde)) // teller opp så lange skuffen inneholder blank
	{
		if (t[i] == ' ')
		{
			bokstaverForran++;		// holder styr på hvor mange blanke det var foran.
		}
		else
		{
			bokstav = true;		// settes til true hvis den møter på en bokstav.
		}
		i++;
	}
	bokstav = false;
	while (!(bokstav && lengde >= 0))			// teller ned fra slutten så lenge det er blanke
	{
		if (t[lengde-1] == ' ')
		{
			bokstaverBak++;		// holder styr på hvor mange blanke det var bak.
		}
		else
		{
			bokstav = true;		// endres når den støter på en bokstav.
		}
		lengde--;
	}
	for (int k = bokstaverForran; k <= (strlen(t) - bokstaverBak); k++, l++)	// starter der den møtte en bokstav, går til der det ikke lengre er bokstaver, og kopierer over innholdet.
	{
		temp[l] = t[k];
	}
	temp[l-1] = '\0';		// leger til på slutten av arrayen.
	strcpy(t, temp);		// kopierer det over i den referanseoverførte arrayen.
}