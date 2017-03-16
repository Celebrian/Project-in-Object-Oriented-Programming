#include <iostream>

using namespace std;

#include "deltagere.h"
#include "funksjoner.h"
#include "const.h"
#include "deltager.h"

Deltagere::Deltagere()
{
	deltagerListe = new List(Sorted);
}

void Deltagere::lagNyDeltager()
{
	int temp;
	do
	{
		temp = les("\nSkriv inn deltagernummer", MINDELTAGER, MAXDELTAGER);
	} while (deltagerListe->inList(temp));
		if (deltagerListe->noOfElements() < MAXDELTAGERE)
	{
		Deltager* nyDeltager;
		nyDeltager = new Deltager(temp);
		deltagerListe->add(nyDeltager);
	}
}

void Deltagere::endreDeltager()
{
	Deltager* temppeker;
	int temp;
	temp = les("\nSkriv inn deltagernummer", MINDELTAGER, MAXDELTAGER);
		if (deltagerListe->inList(temp))
		{
			temppeker = (Deltager*)deltagerListe->remove(temp);
			temppeker->endreNyDeltager();
			deltagerListe->add(temppeker);
		}
		else {
			cout << "\nDeltager finnes ikke." << endl;
		}
}

void Deltagere::skrivUt()
{
	deltagerListe->displayList();
}

void Deltagere::skrivUtValgt()
{
	Deltager* temppeker;
	int temp;
	temp = les("\nSkriv inn deltagernummer", MINDELTAGER, MAXDELTAGER);
	if (deltagerListe->inList(temp))
	{
		temppeker = (Deltager*)deltagerListe->remove(temp);
		temppeker->display();
		deltagerListe->add(temppeker);
	}
	else {
		cout << "\nDeltager finnes ikke." << endl;
	}
}
