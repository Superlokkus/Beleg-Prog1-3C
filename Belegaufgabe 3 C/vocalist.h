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

/*! @brief Creates a new vocalist.
 @returns NULL if allocation fails otherwise a fresh and tasty vocalist
 */
vocalist* newVocaList(void);
/*! @brief Deletes the given, hopefully empty, vocalist.
 @returns False if given list is not empty, otherwise true
 @param *tobedeleted Empty list which has to be deleted
 */
_Bool deleteVocaList(vocalist *tobedeleted); //delete empty vocalist

/*! @brief Add new vocabulary, consisting of an english and german word, to the given list
 @returns True if adding was sucessfull or false if not.
 @param *list Vocalist the words are to be added
 @param *english English word
 @param *german German translation word
 */
_Bool insertVoca(vocalist *list, const char *english, const char *german);
/*! @brief Search and delete vocabulary in given list
 @returns False if vocabulary can't be found
 */
_Bool deleteVoca(vocalist *list,const char *english, const char *german);

char* getGerman(const vocalist *list,const char* english); //Returns NULL if not found
char* getEnglish(const vocalist *list,const char* german); //Retruns NULL if not found

/*! @brief To get the whole dictionary sorted lexically by the german words
@returns Pointer to a char with format <German> <whitespace> <English> <\n>
 @warning Potential memory leak: The application is responsible to free() the returned char* after use.
*/
char* createSortedListGerman(const vocalist *tobelisted, char delimiter[],char pairdelimiter[]);
/*! @brief To get the whole dictionary sorted lexically by the english words
 @returns Pointer to a char with format <English> <Whitespace> <German> <\n>
 @warning Potential memory leak: The application is responsible to free() the returned char* after use.
 */
char* createSortedListEnglish(const vocalist *tobelisted, char delimiter[],char pairdelimiter[]);

#endif
