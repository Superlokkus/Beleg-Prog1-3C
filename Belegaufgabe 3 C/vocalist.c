//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: XXXXX
//
//  vocalist.c
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 07.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#include <stdio.h>
#include "vocalist.h"
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *english;
    char *german;
}wordpair;

int gerCmp(void *first, void *second)
{
    const wordpair *wfirst = (const wordpair *)first;
    const wordpair *wsecond = (const wordpair *)second;
    
    return strcasecmp(wfirst->german, wsecond->german);
}
int engCmp(void *first,void *second)
{
    const wordpair *wfirst = (const wordpair *)first;
    const wordpair *wsecond = (const wordpair *)second;
    
    return strcasecmp(wfirst->english, wsecond->english);
}

vocalist* newVocaList(void)
{
    vocalist *newlist = malloc(sizeof(vocalist));
    if (newlist == NULL) {
        return NULL;
    }
    
    newlist->engList = createList();
    if (newlist->engList == NULL) {
        free(newlist);
        return NULL;
    }
    
    newlist->gerList = createList();
    if (newlist->gerList == NULL) {
        free(newlist);
        return NULL;
    }
    
    return newlist;
}

_Bool deleteVocaList(vocalist *tobedeleted)
{
    if (deleteList(tobedeleted->engList) == OK && deleteList(tobedeleted->gerList) == OK ) {
        free(tobedeleted);
        return true;
    }
    return false;
}
_Bool insertVoca(vocalist *list, const char *english, const char *german)
{
    wordpair *newwordpair = malloc(sizeof(wordpair));
    if (newwordpair == NULL) {
        return false;
    }
    
    newwordpair->english = malloc(sizeof(char)*(strlen(english)+1));
    if (newwordpair->english == NULL) {
        free(newwordpair);
        return false;
    }
    strcpy(newwordpair->english, english);
    
    newwordpair->german = malloc((strlen(german)+1) * sizeof(char));
    if (newwordpair->german == NULL) {
        free(newwordpair->english);
        free(newwordpair);
        return false;
    }
    strcpy(newwordpair->german, german);
    
    if (addItemToList(list->engList, newwordpair, engCmp) != OK) {
        free(newwordpair->english); free(newwordpair->german); free(newwordpair);
        return false;
    }
    
    if (addItemToList(list->gerList, newwordpair, gerCmp) != OK) {
        removeItem(list->engList);
        free(newwordpair->english); free(newwordpair->german); free(newwordpair);
        return false;
    }
    return true;
}
char* getEnglish(const vocalist *list,const char* german)
{
    list->gerList->current = list->gerList->head;
    wordpair *mywordpair = (wordpair *) getSelected(list->gerList);
    if (strcmp(mywordpair->german, german) == 0) {
        return mywordpair->english;
    }

    while(getNext(list->gerList) != NULL) {
        wordpair *mywordpair = (wordpair *) getSelected(list->gerList);
        if(strcmp(mywordpair->german, german) == 0)
            return mywordpair->english;
    }
    return NULL;
}
char* getGerman(const vocalist *list,const char* english)
{
    list->engList->current = list->engList->head;
    wordpair *mywordpair = (wordpair *) getSelected(list->engList);
    if (strcmp(mywordpair->english, english) == 0) {
        return mywordpair->german;
    }
    
    while(getNext(list->engList) != NULL) { 
        wordpair *mywordpair = (wordpair *) getSelected(list->engList);
        if(strcmp(mywordpair->english, english) == 0)
            return mywordpair->german;
    }
    return NULL;
}
char* createSortedListGerman(const vocalist *tobelisted, char delimiter[], char pairdelimiter[])
{
    char *gerlist; //strcat spree spree spree...
    
    if (getFirst(tobelisted->gerList) == NULL) {
        return NULL;
    }
    
    //Allocating of the first element
    wordpair *mywordpair = (wordpair *) getFirst(tobelisted->gerList);
    
    gerlist = malloc((strlen(mywordpair->german) + strlen(delimiter) + strlen(mywordpair->english) + strlen(pairdelimiter) +1 ) * sizeof(char));
    
    if (gerlist == NULL) {
        return NULL;
    }
    
    //Building of the first element
    strcpy(gerlist, mywordpair->german);
    strcat(gerlist, delimiter);
    strcat(gerlist, mywordpair->english);
    strcat(gerlist, pairdelimiter);
    
    //and the possible rest
    tobelisted->gerList->current = tobelisted->gerList->head;
    while (tobelisted->gerList->current->next != NULL) {
        mywordpair = getNext(tobelisted->gerList);
        
        char *tmp = gerlist;
        gerlist = realloc(gerlist, (strlen(gerlist)
                + strlen(mywordpair->german) + strlen(delimiter) + strlen(mywordpair->english) + strlen(pairdelimiter) +1 ) * sizeof(char));
        if (gerlist == NULL) {
            free(tmp); //Could use reallocf() which is, to bad, FreeBSD specific
            return NULL;
        }
        
        
        strcat(gerlist, mywordpair->german);
        strcat(gerlist, delimiter);
        strcat(gerlist, mywordpair->english);
        strcat(gerlist, pairdelimiter);
    }
    return gerlist;
}
char* createSortedListEnglish(const vocalist *tobelisted, char delimiter[], char pairdelimiter[])
{
    char *englist; //strcat spree spree spree...
    if (getFirst(tobelisted->engList) == NULL) {
        return NULL;
    }
    
    //Allocating of the first element
    wordpair *mywordpair = (wordpair *) getFirst(tobelisted->engList);
    
    englist = malloc((strlen(mywordpair->english) + strlen(delimiter) + strlen(mywordpair->german) + strlen(pairdelimiter) +1 ) * sizeof(char)); //Maybe -2 *sizeof(char) because we won't have 3 \0
    
    if (englist == NULL) {
        return NULL;
    }
    
    //Building of the first element
    strcpy(englist, mywordpair->english);
    strcat(englist, delimiter);
    strcat(englist, mywordpair->german);
    strcat(englist, pairdelimiter);
    
    //and the possible rest
    tobelisted->engList->current = tobelisted->engList->head;
    while (tobelisted->engList->current->next != NULL) {
        mywordpair = getNext(tobelisted->engList);
        
        char *tmp = englist;
        englist = realloc(englist, (strlen(englist)
                          + strlen(mywordpair->english) + strlen(delimiter) + strlen(mywordpair->german) + strlen(pairdelimiter) +1 ) * sizeof(char));
        if (englist == NULL) {
            free(tmp); //Could use reallocf() which is, to bad, FreeBSD specific
            return NULL;
        }
        
        strcat(englist, mywordpair->english);
        strcat(englist, delimiter);
        strcat(englist, mywordpair->german);
        strcat(englist, pairdelimiter);
    }
    return englist;
}
_Bool deleteVoca(vocalist *list,const char *english, const char *german)
{
    if (getGerman(list, english) != NULL && getEnglish(list, german) != NULL) { //Both tList current now on item to delete
        wordpair *tobedeleted = (wordpair *) getSelected(list->gerList);
        removeItem(list->engList); free(tobedeleted->english); free(tobedeleted->german); free(getSelected(list->gerList)); removeItem(list->gerList);
        return true;
    }
    return false;
    
}
_Bool emptyAndDeleteVocalist(vocalist *tobekknd)
{
    char *engList = createSortedListEnglish(tobekknd, ";", "\n");
    if (engList == NULL) {
        return false;
    }
    
    int i; char *tokeneng; char *tokenger;
    tokeneng = strtok(engList, ";\n");
    for (i=2; tokeneng != NULL; i++) {
        if (i%2 == 0) {
            tokenger = strtok(NULL, ";\n");
            if (!deleteVoca(tobekknd, tokeneng, tokenger))
            {
                free(engList);
                return false;
            }
        }
        else {
            tokeneng = strtok(NULL, ";\n");
        }
    }
    
    if (!deleteVocaList(tobekknd)) {
        free(engList);
        return false;
    }
    
    
    free(engList);
    return true;
}

