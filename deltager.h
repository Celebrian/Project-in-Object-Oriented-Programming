#if !defined(__DELTAGER_H)
#define  __DELTAGER_H

//Deltager klasse deklarasjon

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"

class Deltager : public NumElement {
private:
	char* navn;
	char nasjon[LANDSKODE + 1];
	kjonn gender;
public:
	Deltager(int n);
	void endreNyDeltager();
	virtual void display();
	void displayAll();
	bool sjekkLand(char ch[LANDSKODE]);
};


#endif