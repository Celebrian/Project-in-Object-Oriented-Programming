#if !defined(__ENUM_H)
#define  __ENUM_H

//ENUM'er:

enum kjonn {				//Kjønn
	jente, gutt
};

enum resultatType {			//Resultat; tid eller poeng
	poeng, tid
};

enum presReg {					// KANSKJE UBRUKELIG????
	tidel, hundredel, tusendel, poengx, poengxx
};

enum medalje {				//Type medalje; gull, sølv eller bronse
	gull, solv, bronse
};

enum filtype {				// hvilken type filnavn som skal lages.
	startliste, resultatliste
};

enum plusminus {
	minus, pluss
};

#endif