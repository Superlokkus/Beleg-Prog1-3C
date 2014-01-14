//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
//
//  persist_vocalist.h
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 14.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#ifndef Belegaufgabe_3_C_persist_vocalist_h
#define Belegaufgabe_3_C_persist_vocalist_h

#include "vocalist.h"
#include <stdlib.h>

#define worddelimiter ";"

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else
typedef	int	_Bool;
#define	false	0
#define	true	1
#endif

/*! @brief Reads in given file to append to the given vocalist
 @returns True if allocation and adding was succesfull otherwise false
 @param *filetodict File from where the vocabulary is to be read in
 @param *dictToBeExtended Vocalist where the read vocabularys are added to
 */
_Bool readDictFromFile(FILE *filetodict,vocalist *dictToBeExtended);
/*! @brief Saves given vocalist to the file, overwriting any old entries in the file
 @attention Given File will be truncated
 @param *fileToTruncAndSaved File which will be overwritten with dicttosave
 @param *dicttosave Vocalist to be saved
 */
_Bool saveDictToFile(FILE *fileToTruncAndSaved,vocalist *dicttosave);



#endif
