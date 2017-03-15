#if !defined(__GREN_H)
#define  GREN_H

//Gren klasse deklarasjon

#include "const.h"
#include "enum.h"
#include "ListTool2B.h"
#include "ovelse.h"

class Gren : public TextElement {
	resultatType typeResultat;
	int antallOvelser;
	Ovelse* ovelser[MAXOVELSER];
public:

};

#endif