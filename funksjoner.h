#if !defined(__FUNKSJONER_H)
#define  FUNKSJONER_H

//Hjelpefunksjoner deklarasjoner

#include <fstream>

using namespace std;

//Skriv meny funksjon
void skrivMeny();

//Meny funksjon
void Meny();

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

//Andre funksjoner
bool kunTall(char t[]);				//Skjekker at en text bare inneholder tal
bool kunTallFloat(char t[]);
void gjorStor(char s[]);
bool erLik(const char t[], const char s[]);
void fjernBlanke(char t[]);

#endif