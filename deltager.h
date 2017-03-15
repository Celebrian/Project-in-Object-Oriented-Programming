#if !defined(__DELTAGER_H)
#define  __DELTAGER_H

//Deltager klasse deklarasjon
#include <iostream>

using namespace std;

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"

class Deltager : public NumElement {
private:
	char* navn;
	char nasjon[LANDSKODE];
	kjonn gender;
public:

};





#endif