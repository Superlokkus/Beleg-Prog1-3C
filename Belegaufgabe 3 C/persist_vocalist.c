//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: XXXXX
//
//  persist_vocalist.c
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 14.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#include <stdio.h>
#include "persist_vocalist.h"
#include <string.h>
#define bufflen 1024

_Bool readDictFromFile(FILE *filetodict,vocalist *dictToBeExtended)
{
    char buff[bufflen];
    while (fgets(buff, bufflen, filetodict) != NULL ) {
        char *eng = strtok(buff, ";\n"); char *ger = strtok(NULL, ";\n");
        if (eng == NULL || ger == NULL) {
            break;
        }
        if (!insertVoca(dictToBeExtended, eng, ger)) {
            return false;
        }
    }
    if (!feof(filetodict)) {
        return false;
    }
    return true;
}
_Bool saveDictToFile(FILE *fileToTruncAndSaved,vocalist *dicttosave)
{
    //Truncate file
    fileToTruncAndSaved = freopen(NULL, "w", fileToTruncAndSaved);
    if (fileToTruncAndSaved == NULL) {
        perror("Truncating file failed because of");
    }
    char *englist = createSortedListEnglish(dicttosave, worddelimiter, "\n");
    if (englist == NULL) {
        return false;
    }
    fprintf(fileToTruncAndSaved, "%s",englist);
    free(englist);
    
    return true;
}
