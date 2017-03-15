#if !defined(__FUNKSJONER_H)
#define  FUNKSJONER_H

#include <fstream>
using namespace std;

//Hjelpefunksjoner deklarasjoner

void skrivMeny();
void skrivMenyN();
void skrivMenyD();
void skrivMenyG();
void skrivMenyO();
void skrivMenyOL();
void skrivMenyOR();

void Meny();
void MenyN();
void MenyD();
void MenyG();
void MenyO();
void MenyOL();
void MenyOR();


char les();
int les(char* t, int min, int max);
void les(const char t[], char s[], const int LEN);
void les(const char* t, char* &s);
void lesInnFraFil(char* &s, ifstream & inn);


#endif