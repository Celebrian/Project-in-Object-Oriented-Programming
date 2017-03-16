#if !defined(__FUNKSJONER_H)
#define  FUNKSJONER_H

//Hjelpefunksjoner deklarasjoner

#include <fstream>

using namespace std;

//Skriv meny funksjoner
void skrivMeny();
void skrivMenyN();
void skrivMenyD();
void skrivMenyG();
void skrivMenyO();
void skrivMenyOL();
void skrivMenyOR();

//Meny funksjoner
void Meny();
void MenyN();
void MenyD();
void MenyG();
void MenyO();
void MenyOL();
void MenyOR();

//Les funksjoner
char les();
int les(char* t, int min, int max);
void les(const char t[], char s[], const int LEN);
void les(const char* t, char* &s);
void lesInnFraFil(char* &s, ifstream & inn);
int lesTelefon();

//Skjekk dato funksjoner
int lesDato();								//Sjekker at dato finnes
bool skuddaar(int aa);						//  Hentet/kopiert (nesten) RETT
bool finnesDato(int da, int ma, int aa);	//     fra OPPG_20.

//Leser inn klokkeslett
int lesKlokkeSlett();

//MenyN() funksjoner:
void registrerNasjon();
void endreNasjon();
void hoveddataNasjon();
void deltagereNasjon();
void alleDataEnNasjon();

//MenyD funksjoner:
void registrerDeltager();
void endreDeltager();
void hovedDeltager();
void gittDeltager();

#endif