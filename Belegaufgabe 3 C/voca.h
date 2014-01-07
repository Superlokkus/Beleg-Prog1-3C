//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
//
//  voca.h
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 06.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#ifndef Belegaufgabe_3_C_voca_h
#define Belegaufgabe_3_C_voca_h

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
typedef	int	_Bool;
#define	false	0
#define	true	1
#endif

typedef unsigned long voca; //used as UID


voca initVoca(); //Empty voca
void ddelVoca(voca);

char* getenglish(voca); //Returns NULL if empty
char* getgerman(voca); //Returns NULL if empty

_Bool setenglish(voca); //Returns fail if allocation fails
_Bool setgerman(voca); //Returns fail if allocation fails



#endif
