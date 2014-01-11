//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
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

/*! @typedef vocalist
 @brief Representation of a dictionary for use with the functions vocalist libray.
 @warning Do not use the members by ourself.
 */
typedef struct {
    tList *engList;
    tList *gerList;
}vocalist;


vocalist* newVocaList(void); //Returns NULL if allocation fails
_Bool deleteVocaList(vocalist *tobedeleted); //delete empty vocalist

_Bool insertVoca(vocalist *list, const char *english, const char *german); //Returns success==1 or fail==0
_Bool deleteVoca(vocalist *list,const char *english, const char *german); //Search and delete in List

char* getGerman(vocalist *list,const char* english); //Returns NULL if not found
char* getEnglish(vocalist *list,const char* german); //Retruns NULL if not found

/*! @brief To get the whole dictionary sorted lexically by the german words
@returns <German> <whitespace> <English> <\n>
 @remakrs Delimiter may be changed in the future
*/
char* getSortedListGerman(const vocalist *tobelisted);
char* getSortedListEnglish(const vocalist *tobelisted);//Arrangement <german> <english> \n Subject may to change: Whitespace delimited


#endif
