#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <fstream>
#include <cctype>

#include "const.h"
#include "funksjoner.h"
#include "deltager.h"
#include "nasjoner.h"


using namespace std;

extern Deltager deltagerobjekt;
extern Nasjoner nasjonobjekt;

char les() // leser inn et ikke-blankt tegn.
{
	char ch;
	cout << "\n\nKommando:  ";
	cin >> ch;  cin.ignore();
	return (toupper(ch));
}

int les(char* t, int min, int max) { // leser inn et tall mellom to grenser.
	int tall;
	do {
		cout << '\t' << t << " (" << min << '-' << max << "):  ";
		cin >> tall;  cin.ignore();
	} while (tall < min || tall > max);
	return tall;
}

void les(const char t[], char s[], const int LEN) { // leser inn en text
	do {
		cout << '\t' << t << ": ";	cin.getline(s, LEN);
	} while (strlen(s) == 0);
}

void lesInnFraFil(char* &s, ifstream & inn)
{ // funksjon for a hente char til pointers når man leser fra fil
	char temp[MAXTXT]; // lager en temp array
	do
	{
		inn.getline(temp, MAXTXT); // henter teksten fra fil
	} while (strlen(temp) == 0);
	s = new char[strlen(temp) + 1]; // lager array med spesifik storrelse
	strcpy(s, temp); // kopierer over i arrayen s
	s[strlen(temp)] = '\0'; // legger til pa slutten av s
}

void les(const char* t, char* &s) // tar med char pointer og en pointer
{	// pointeren er referanseoverfort for a ikke tulle med dens 
	// originale plass i memory.
	char temp[MAXTXT]; // lager en array med max strorrelse
	do
	{
		cout << t;
		cin.getline(temp, MAXTXT); // henter tenkst og legger den inn i temp
	} while (strlen(temp) == 0);
	s = new char[strlen(temp) + 1]; // lager array med fikset storrelse
	strcpy(s, temp); // kopierer fra temp og inn i s
	s[strlen(temp)] = '\0'; // legger inn pa slutten av arrayen.
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

void skrivMenyN()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny nasjon";
	cout << "\n\tE = Endre en nasjon";
	cout << "\n\tA = Skriv alle data om alle nasjoner";
	cout << "\n\tT = Skriv en nasjons deltagertropp";
	cout << "\n\tS = Skriv alle data om en gitt nasjon";
	cout << "\n\tQ = Forrige meny";
}

void skrivMenyD()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny deltaker";
	cout << "\n\tE = Endre en deltaker";
	cout << "\n\tA = Skriv alle data om alle deltakere";
	cout << "\n\tS = Skriv alle data om en gitt deltaker";
	cout << "\n\tQ = Forrige meny";
}

void skrivMenyG()
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny gren";
	cout << "\n\tE = Endre en gren";
	cout << "\n\tA = Skriv alle data om alle grener";
	cout << "\n\tS = Skriv alle data om en gitt gren";
	cout << "\n\tQ = Forrige meny";
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
		case 'N': MenyN(); break;
		case 'D': MenyD();  break;
		case 'G': MenyG(); break;
		case 'O': MenyO();   break;
		case 'M': cout << "\nMedaljeoveriskt";  break;
		case 'P': cout << "\nPoengoveriskt";    break;
		default:  skrivMeny();       break;
		}
		kommando = les();
	}
}

void MenyN()
{
	char valg;                //  Brukerens valg.
	skrivMenyN();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': cout << "\nRegistrer ny nasjon"; break;
		case 'E': cout << "\nEndrer nasjon";  break;
		case 'A': cout << "\nSkriver alle"; break;
		case 'T': cout << "\nskriver tropp";   break;
		case 'S': cout << "\skriver alle data";  break;
		default:  skrivMenyN();       break;
		}
		valg = les();
	}
}

void MenyD()
{
	char valg;                //  Brukerens valg.
	skrivMenyD();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': cout << "\nRegistrer ny deltager"; break;
		case 'E': cout << "\nEndrer deltager";  break;
		case 'A': cout << "\nSkriver alle"; break;
		case 'S': cout << "\skriver alle data";  break;
		default:  skrivMenyD();       break;
		}
		valg = les();
	}
}

void MenyG()
{
	char valg;                //  Brukerens valg.
	skrivMenyG();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': cout << "\nRegistrer ny gren"; break;
		case 'E': cout << "\nEndrer gren";  break;
		case 'A': cout << "\nSkriver alle"; break;
		case 'S': cout << "\skriver alle data";  break;
		default:  skrivMenyG();       break;
		}
		valg = les();
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
		case 'S': cout << "\skriver data om alle øvelser i: " << tempNavn;  break;
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

void registrerNasjon() {
	nasjonobjekt.registrerNasjon();
}

void endreNasjon() {

}

void hoveddataNasjon() {

}

void deltagereNasjon() {

}

void alleDataEnNasjon() {

}

void registrerDeltager()
{
	Deltager
}

void endreDeltager()
{

}

void hovedDeltager()
{

}

void gittDeltager()
{

}
