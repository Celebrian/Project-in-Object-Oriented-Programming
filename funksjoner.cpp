#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>

using namespace std;

#include "const.h"
#include "funksjoner.h"
#include "deltager.h"
#include "deltagere.h"
#include "nasjoner.h"
#include "grener.h"
#include "poeng.h"



extern Deltagere deltagerobjekt;
extern Grener grenobjekt;
extern Nasjoner nasjonerObjekt;
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
	char temp[TELEFONNUMMER + 10];
	int gyldigNummer;

	do
	{
		les("Skriv inn telefonnummer, ikke landskode, kun tall", temp, TELEFONNUMMER);
	} while (!kunTall(temp));			//Leser inn nummer til det er bare tall
	gyldigNummer = atoi(temp);			//Caster til int, siden det bare er tall
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

void skrivMenyO()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny øvelse";
	cout << "\n\tE = Endre en øvelse";
	cout << "\n\tA = Skriv alle data om alle øvelser";
	cout << "\n\tL = Startliste undermeny";
	cout << "\n\tR = Resultatliste undermeny";
	cout << "\n\tQ = Forrige meny";
}

void skrivMenyOL()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv deltakerliste";
	cout << "\n\tN = Ny deltakerliste";
	cout << "\n\tE = Endre deltakerliste";
	cout << "\n\tF = Fjerne deltakerliste";
	cout << "\n\tQ = Forrige meny";
}

void skrivMenyOR()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv resultatliste";
	cout << "\n\tE = Ny resultatliste";
	cout << "\n\tF = Fjerne resultatliste";
	cout << "\n\tQ = Forrige meny";
}

void Meny()
{
	char kommando;                //  Brukerens valg.
	skrivMeny();                  //  skriver ut meny med valg.

	kommando = les();             //  Leser brukerens valg.
	while (kommando != 'X') {
		switch (kommando) {
		case 'N': nasjonerObjekt.MenyN();		break;
		case 'D': deltagerobjekt.MenyD();  break;
		case 'G': grenobjekt.MenyH(); break;
		case 'O': MenyO();   break;
		case 'M': cout << "\nMedaljeoveriskt";  break;
		case 'P': testPoeng();;    break;
		default:  skrivMeny();       break;
		}
		kommando = les();
	}
}

void MenyO()
{
	char* tempNavn;
	les("\nLes inn navn", tempNavn);
	
	
	
	// FIKS DETTE SENERE (sjekk navn)





	char valg;                //  Brukerens valg.
	skrivMenyO();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': cout << "\nRegistrer ny øvelse i " << tempNavn; break;
		case 'E': cout << "\nEndrer en øvelse i: " << tempNavn;  break;
		case 'F': cout << "\nFjerner en ævelse i: " << tempNavn;; break;
		case 'S': cout << "\nSkriver data om alle øvelser i: " << tempNavn;  break;
		case 'L': MenyOL(); break;
		case 'R': MenyOR(); break;
		default:  skrivMenyO();       break;
		}
		valg = les();
	}
}

void MenyOL()
{
	int temp;
	temp = les("\nSkriv inn nummer", MINDELTAGER, MAXDELTAGER);


	// FIKS SENERE (SJEKKE NUMMER).



	char valg;                //  Brukerens valg.
	skrivMenyOL();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'S': cout << "\nSkriver deltagerliste om: " << temp; break;
		case 'N': cout << "\nNy deltagerliste i øvelse: " << temp;  break;
		case 'E': cout << "\nEndrer liste om " << temp; break;
		case 'F': cout << "\nSletter deltagerliste i: " << temp;   break;
		default:  skrivMenyOL();       break;
		}
		valg = les();
	}
}

void MenyOR()
{
	int temp;
	temp = les("\nSkriv inn nummer", MINDELTAGER, MAXDELTAGER);


	// FIKS SENERE (SJEKKE NUMMER).



	char valg;                //  Brukerens valg.
	skrivMenyOR();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'S': cout << "\nSkriver resultatliste om: " << temp; break;
		case 'N': cout << "\nNy deltagerliste i øvelse: " << temp;  break;
		case 'F': cout << "\nSletter resultatliste i: " << temp;   break;
		default:  skrivMenyOR();       break;
		}
		valg = les();
	}
}

int lesKlokkeSlett()
{
	int klokka;
	do
	{
		cout << "\nLes inn klokkeslett (TTMM)" << endl;
		cin >> klokka;
	} while (!isdigit(klokka) || (klokka < 0)
		|| ((klokka / 100) > 23) || ((klokka % 100) > 59));
	return klokka;
}
	
int lesDato()						//LESE LOVELIG DATO
{
	int dato, aaaa, mm, dd;			//Variabler for dato, dag, måned og år
	do
	{
		cout << "\tSkriv inn gyldig dato fra "	//Ber om gyldig dato
			<< 0 << " - " << 3000				//Mellom årstall
			<< " (p† formen: ††††mmdd) ";		//På formen aaaammdd
		cin >> dato; cin.ignore();				//Leser inn og forkaster \n
		aaaa = dato / 10000;					//Henter bare året fra dato
		mm = (dato / 100) % 100;				//Henter måneden fra dato
		dd = dato % 100;						//Henter dagen fra dato

	} while ((!isdigit(dato)) || !finnesDato(dd, mm, aaaa));		//Så lenge datoen ikke fins
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

void testPoeng() // TESTFUNKSJON, SKAL SLETTES SENERE.
{
	char temp[LANDSKODE];
	int tempint;
	lesNasjon("\nHvilken nasjon skal få poeng?", temp, LANDSKODE);
	cout << "\nHvor mange poeng" << endl;
	cin >> tempint;
	poengobjekt.oppdaterPoeng(temp, tempint);
	poengobjekt.displayPoeng();
}