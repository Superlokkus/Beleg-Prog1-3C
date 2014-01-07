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

typedef struct{
    char* english;
    char* german;
}voca;

typedef tList vocalist;

vocalist* newVocaList(void); //Returns NULL if allocation fails
void deleteVocaList(vocalist); //Empties and deletes

_Bool insertVoca(vocalist); //Returns success (true) or fail (false)




#endif
