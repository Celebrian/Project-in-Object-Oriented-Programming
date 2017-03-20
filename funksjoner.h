#if !defined(__FUNKSJONER_H)
#define  FUNKSJONER_H

//Hjelpefunksjoner deklarasjoner

#include <fstream>

using namespace std;

//Skriv meny funksjoner
void skrivMeny();
void skrivMenyD();
void skrivMenyG();
void skrivMenyO();
void skrivMenyOL();
void skrivMenyOR();

//Meny funksjoner
void Meny();
void MenyD();
void MenyG();
void MenyO();
void MenyOL();
void MenyOR();

//Les funksjoner
char les();									//Leser, returnerer og upcaser en enkel char
int les(char* t, const int min, const int max);		//Leser og returnerer en int mellom MIN og MAX
void les(const char t[], char s[], const int LEN);	//Leser inn text i S, max LEN lang
void les(const char* t, char* &s);
void lesNasjon(const char t[], char s[], const int LEN);	//Leser inn en landskode i S
void lesInnFraFil(char* &s, ifstream & inn);
int lesTelefon();							//Leser inn et lovelig telefonnummer

//Skjekk dato funksjoner
int lesDato();								//Sjekker at dato finnes
bool skuddaar(int aa);						//  Hentet/kopiert (nesten) RETT
bool finnesDato(int da, int ma, int aa);	//     fra OPPG_20 - Endret av PK for oblig_3

//Leser inn klokkeslett
int lesKlokkeSlett();

//MenyD funksjoner:
void registrerDeltager();
void endreDeltager();
void hovedDeltager();
void gittDeltager();

//MenyG funksjoner:
void registrerGren();
void endreGren();
void hovedGren();
void gittGren();


//Andre funksjoner
bool kunTall(char t[]);				//Skjekker at en text bare inneholder tall

#endif