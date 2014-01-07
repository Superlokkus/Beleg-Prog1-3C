//
//  vocalist.h
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 07.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#ifndef Belegaufgabe_3_C_vocalist_h
#define Belegaufgabe_3_C_vocalist_h

#include "list.h"

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
typedef	int	_Bool;
#define	false	0
#define	true	1
#endif


typedef tList vocalist;

vocalist* newVocaList(void); //Returns NULL if allocation fails
void deleteVocaList(vocalist *tobedeleted); //Empties and deletes

_Bool insertVoca(const char *english, const char *german); //Returns success==1 or fail==0
_Bool deleteVoca(const char *english, const char *german); //Search and delete in List

char* getGerman(const char* english); //Returns NULL if not found
char* getEnglish(const char* german); //Retruns NULL if not found

char* getSortedListGerman(const vocalist *tobelisted);//Subject may to change: Whitespace delimited
char* getSortedListEnglish(const vocalist *tobelisted);//Subject may to change: Whitespace delimited


#endif
