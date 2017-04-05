#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>

using namespace std;

#include "gren.h"
#include "funksjoner.h"


Gren::Gren(char * ch) : TextElement(ch)
{
	navn = ch;										// navnet p� grenen
	char chr;
	skrivShit();									// skriver menyen med oversit over de forksjellige m�tene og registrere poeng.
	chr = les();									// leser inn brukerens valg.
	switch (chr){									// resultat blir:
	case 'T': typeResultat = tidel; break;			// MMSST
	case 'H': typeResultat = hundredel; break;		// MMSSHH
	case 'D': typeResultat = tusendel; break;		// MMSSTTT
	case 'P': typeResultat = poengx; break;			// PoengX
	case 'X': typeResultat = poengxx; break;		// PoengXX
	default: skrivShit(); break; 
	}
	antallOvelser = 0;								// en gren har ingen �velser da den blir opprettet, disse legges inn siden.
}

void Gren::skrivShit()								// navnet kommer av at jeg var tr�tt etter en lang dag.
{
	cout << "\n\tT for tidel" 
		<< "\n\tH for hundredel" 
		<< "\n\tD for tusendel" 
		<< "\n\tP for poengX" 
		<< "\n\tX for poengXX" << endl;
}

Gren::Gren(char ch[], ifstream & inn) : TextElement(ch)
{
	navn = new char[strlen(ch) + 1]; // lager array med spesifik storrelse
	strcpy(navn, ch); // kopierer over i arrayen ch
	int temp; inn >> temp; inn.ignore(); // leser inn 0 eller 1 fra fil
	switch (temp) {
	case 0: typeResultat = tidel; break;		//MMSST
	case 1: typeResultat = hundredel; break;	//MMSSHH
	case 2: typeResultat = tusendel; break;		//MMSSTTT
	case 3: typeResultat = poengx; break;		//PoengX
	case 4: typeResultat = poengxx; break;		//PoengXX
	default: break; 
	}
	inn >> antallOvelser; inn.ignore(); 
	//for (int i = 1; i <= antallOvelser; i++) // looper gjennom hele arrayen med ovelser
	//{
		//inn >> ovelser[i];	// leser inn ovelsenummeret
	//}
}

void Gren::SkrivGrenTilFil(ofstream & ut)	// skriver grenens data til fil.
{
	ut << navn << '\n';	// skriver ut navn
	switch (typeResultat) {
	case tidel: ut << tidel << '\n'; break;
	case hundredel: ut << hundredel << '\n'; break;
	case tusendel: ut << tusendel << '\n'; break;
	case poengx: ut << poengx << '\n'; break;
	case poengxx: ut << poengxx << '\n'; break;
	default: break; 
	}
	ut << antallOvelser << '\n';
	//for (int i = 1; i <= antallOvelser; i++)	// looper hele ovelser arrayen.
	//{
		//ut << " " << ovelser[i];	// skriver ut ovelsenummer.
	//}
}

void Gren::endreNyGren()		// endrer data p� en gren, bare navn er lov � endre.
{
	cout << "\nVil du endre p� navnet? J(a) / N(ei) " << endl;
	char ch = les();
	if(ch != 'N')
	{
		delete[] navn;			// sletter det eksisterende navnet
		les("\n\tLes inn nytt navn", navn);	// leser det inn p� nytt.
	}
}

void Gren::display()	// skriver ut data om gren til skjerm.
{
	cout << "\n\tNavn: " << navn
		<< "\n\tRegistrering av prestasjon: ";
	switch (typeResultat) {
	case tidel: cout << "tidel" << '\n'; break;
	case hundredel: cout << "hundredel" << '\n'; break;
	case tusendel: cout << "tusendel" << '\n'; break;
	case poengx: cout << "poengx" << '\n'; break;
	case poengxx: cout << "poengxx" << '\n'; break;
	default: break;
	}
		cout << "\n\tAntall �velser i gren: " << antallOvelser << endl;
}

void Gren::displayValgt()			// skriver ut alle data om en valgt gren.
{
	display();						// skriver data om grenen.
	for (int i = 1; i <= antallOvelser; i++)
	{	
		ovelser[i]->skrivAlt();		// skriver data om alle �velse i grenen.
	}
}


void Gren::MenyO()
{
	char valg;                //  Brukerens valg.
	skrivMenyO();                  //  skriver ut meny med valg.

	valg = les();             //  Leser brukerens valg.
	while (valg != 'Q') {
		switch (valg) {
		case 'N': nyOvelse(); break;			// lager ny �velse
		case 'E': endreOvelse();  break;		// endrer p� �velsen
		case 'F': fjernOvelse(); break;			// sletter en �velse
		case 'A': skrivAlle();  break;			// skriver hoveddata om alle �velse
		case 'L': MenyOL(); break;				// meny for startliste
		case 'R': resultatListeMeny(); break;	// meny for resultatliste
		default:  skrivMenyO();       break;	
		}
		valg = les();
	}
}

void Gren::MenyOL()
{
	bool finnesOvelse = false;
	int temp;
	char valg;                //  Brukerens valg.

	temp = les("\nSkriv inn �velsenummer", 1000, 9999);
	for (int i = 1; i <= antallOvelser; i++)			//Looper gjennom alle �velsene
	{
		if (ovelser[i]->sjekkID(temp))					//Skjekker om id matcher
		{
			finnesOvelse = true;
			skrivMenyOL();                  //  skriver ut meny med valg.
	
			valg = les();             //  Leser brukerens valg.
			while (valg != 'Q') {
				switch (valg) {
				case 'S': ovelser[i]->skrivStartliste();	break;
				case 'N': ovelser[i]->nyStartliste();		break;
				case 'E': ovelser[i]->endreStartliste();	break;
				case 'F': ovelser[i]->fjernDeltagerliste();	break;
				default:  skrivMenyOL();					break;
				}
				valg = les();
			}
		}
	}
	if (!finnesOvelse)
	{
		cout << "\n\tIngen �velser med denne ID" << endl;
	}
}

void Gren::skrivMenyO()				// mulige valg for �velser.
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tN = Registrer en ny �velse";
	cout << "\n\tE = Endre en �velse";
	cout << "\n\tA = Skriv alle data om alle �velser";
	cout << "\n\tL = Startliste undermeny";
	cout << "\n\tR = Resultatliste undermeny";
	cout << "\n\tQ = Forrige meny";
}

void Gren::skrivMenyOL()		// mulige valg for startliste.
{
	cout << "\n\nFoLGENDE KOMMANDOER ER TILGJENGELIGE:";
	cout << "\n\tS = Skriv deltakerliste";
	cout << "\n\tN = Ny deltakerliste";
	cout << "\n\tE = Endre deltakerliste";
	cout << "\n\tF = Fjerne deltakerliste";
	cout << "\n\tQ = Forrige meny";
}

void Gren::returnNavn(char t[]) // returnerer navnet p� en gren, via � kopiere det inn i et medsendt array.
{
	strcpy(t, text);
}

void Gren::nyOvelse()					// oppretter ny �velse.
{
	bool idfinnesikke = true;
	bool navnfinnesikke = true;
	if (antallOvelser < MAXOVELSER)		// sjekker om det er plass til en ny �velse.
	{
		int tempID;
		tempID = les("\nLes inn unik ID", MINOVNR, MAXOVNR);	// leser inn en ID
		if(antallOvelser >= 0)	// sjekker om det finnes en �velse allerede
		{
			for (int i = 1; i <= antallOvelser; i++)	// g�r gjennom alle eksisterende �velser.
			{
				if (ovelser[i]->sjekkID(tempID))		// sjekker om den innlsete ID-en allerede finnes i en �velse.
				{
					idfinnesikke = false;				// hvis den finnes blir bool-en til false.
				}
			}
			if (idfinnesikke)							// kj�res hvis boolen er true.
			{
				char* temp;
				les("\n\tLes inn navn p� ovelse", temp);	// leser inn navn p� �velse.
				for (int j = 1; j <= antallOvelser; j++)
				{
					if (ovelser[j]->sjekkNavn(temp))	// sjekker om navnet allerede finnes.
					{
						navnfinnesikke = false;			//bool blir false hvis navnet finnes.
					}				
				}
				if (navnfinnesikke)						// hvis navnet ikke allerede var opptatt.
				{
					ovelser[++antallOvelser] = new Ovelse(tempID, temp, typeResultat); // opprett en ny �velse bakerst i �velse arrayen ved hjelp av antallOvelser. teller ogs� opp antallOvelser.
				}
				else
				{
					cout << "\n\tNavn finnes allerede. " << endl;
				}
			}
			else
			{
				cout << "\n\tID finnes alerede." << endl;
			}
		}
	}
	else
	{
		cout << "\n\tOvelser er allerede fullt." << endl;
	}
}

void Gren::endreOvelse()						// endrer p� en �velse.
{
	bool ovelseFinnes = false;
	if (antallOvelser > 0)		// sjekker om det finnes noen �velser.
	{
		int tempID;
		tempID = les("\nLes inn ID p� �velse du vil endre", MINOVNR, MAXOVNR);	// leser inn id p� �velsen man vil endre.
		for (int i = 1; i <= antallOvelser; i++)								// g�r gjennom alle �velser.
		{
			if (ovelser[i]->sjekkID(tempID))									// sjekker om ID-en finnes.
			{
				ovelseFinnes = true;											// bool blir true.
				tempID = i;														// tempID blir nummeret i arrayen der man fikk match med den innleste ID-en.
			}
		}
		if (ovelseFinnes)														// hvis man fikk match.
		{
			ovelser[tempID]->endreOvelsen();									// kj�r funksjon p� det objektet som pekeren i arrayen peker p�, der matchen var.
		}	
		else
		{
		cout << "\n\tOvelsen med dette nummeret finnes ikke." << endl;
		}
	}
	else
	{
		cout << "\n\tDet finnes ingen ovelser for �yeblikket" << endl;
	}
}

void Gren::skrivAlle()								// skriver hoveddata om alle �velser
{
	if (antallOvelser > 0) {						// sjekker om det finnes noen �velser.
		for (int i = 1; i <= antallOvelser; i++)	// g�r gjennom alle �velser som finnes.
		{
			ovelser[i]->skrivAlt();					// kj�rer skriv funksjon p� alle.
		}
	}
	else
	{
		cout << "\n\tIngen ovelser. " << endl;
	}
}

void Gren::skrivOvelseTilFil(ofstream & ut)		// skriver �velser til fil.
{
	ut << antallOvelser << endl;				// skriv f�rst ut antall for � gj�re det lettere � lese inn.
	for (int i = 1; i <= antallOvelser; i++)	// g�r gjennom alle �velser.
	{
		ovelser[i]->skrivTilFil(ut);			// skriv ut data om hver enkelt.
	}
}

void Gren::lesOvelseFraFil(ifstream & inn)	// leser inn alle �velser fra fil.
{
	int temp, temp2;
	inn >> temp;							// leser inn antall �velser, som skal ligge f�rst p� fila
	for (int i = 1; i <= temp; i++)			// kj�rer opp til den innleste antall �velser.
	{
		inn >> temp2; inn.ignore();			// leser inn �velsenummer.
		ovelser[i] = new Ovelse(inn, temp2,typeResultat);	// oppretter en ny �velse med det innleste nummeret.
	}
}

void Gren::resultatListeMeny()			// meny for resultatliste.
{
	bool fantOvelse = false;
	int temp;
	temp = les("\nSkriv inn nummer", MINOVNR, MAXOVNR);		// leser inn �velser du vil se resultatlistemenyen til.
	for (int i = 1; i <= antallOvelser; i++)				// g�r gjennom alle �velser.
	{
		if (ovelser[i]->sjekkID(temp))						// sjekker om �velsen finnes.
		{
			ovelser[i]->MenyOR();							// skriver menyen.
			fantOvelse = true;
		}
	}

	if (!fantOvelse)
	{
		cout << "\n\t�velsen finnes ikke!" << endl;
	}
}

void Gren::fjernOvelse()							// fjerner en �velse og alle relaterte data.
{
	bool ovelseFinnes = false;
	if (antallOvelser > 0)
	{
		int tempID;
		tempID = les("\nLes inn ID p� �velse du vil slette", MINOVNR, MAXOVNR);	//leser inn en ID.
		for (int i = 1; i <= antallOvelser; i++)								// g�r gjennom alle �velser.
		{
			if (ovelser[i]->sjekkID(tempID))									// sjekker om en �velse med innskrevet ID finnes.
			{
				ovelseFinnes = true;											// hvis den finnes blir bool true.
				tempID = i;
			}
		}
		if (ovelseFinnes)														// hvis bool er true.
		{
			ovelser[tempID]->fjernOvelse();										// kj�r fjern funksjonen p� �velsen.
			delete ovelser[tempID];												// slett selve �velsen fra arrayen.
			for (int j = tempID; j <= antallOvelser - 1; j++)					// loop gjennom restrerende �velser.			
			{
				ovelser[tempID] = ovelser[tempID + 1];							// flytt de bakover for � tette hull i arrayen.
			}
		}
		else
		{
			cout << "\n\tOvelsen med dette nummeret finnes ikke." << endl;
		}
		antallOvelser--;														// tell ned antallOvelser med 1.
	}
	else
	{
		cout << "\n\tDet finnes ingen ovelser for �yeblikket" << endl;
	}
}