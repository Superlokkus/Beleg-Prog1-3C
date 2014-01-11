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
    
    newwordpair->english = malloc(sizeof(english));
    if (newwordpair->english == NULL) {
        free(newwordpair);
        return false;
    }
    strcpy(newwordpair->english, english);
    
    newwordpair->german = malloc(sizeof(german));
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
        free(newwordpair->english); free(newwordpair->german); free(newwordpair);
        return false;
    }
    return true;
}
char* getEnglish(vocalist *list,const char* german)
{
    list->gerList->current = list->gerList->head;
    wordpair *mywordpair = (wordpair *) getSelected(list->gerList);
    if (strcmp(mywordpair->german, german) == 0) {
        return mywordpair->english;;
    }

    while(true) { //Infinite loop danger
        if (getNext(list->gerList) == NULL) {
            return NULL;
        }

        if(strcmp(mywordpair->german, german) == 0)
            return mywordpair->english;
    }
}
char* getGerman(vocalist *list,const char* english)
{
    list->engList->current = list->engList->head;
    wordpair *mywordpair = (wordpair *) getSelected(list->engList);
    if (strcmp(mywordpair->english, english) == 0) {
        return mywordpair->german;
    }
    
    while(true) { //Infinite loop danger
        if (getNext(list->engList) == NULL) {
            return NULL;
        }
        if(strcmp(mywordpair->english, english) == 0)
            return mywordpair->german;
    }
}
char* getSortedListGerman(const vocalist *tobelisted)
{
    char *gerlist; //Momomo-Monster listlistlist... Todo But how to free?!
    const char delimiter[] = {" "};
    const char pairdelimiter[] = {"\n"};
    
    if (getFirst(tobelisted->gerList) == NULL) {
        return NULL;
    }
    
    //Allocating of the first element
    wordpair *mywordpair = (wordpair *) getFirst(tobelisted->gerList);
    
    gerlist = malloc(sizeof(mywordpair->german) + sizeof(delimiter) + sizeof(mywordpair->english) + sizeof(pairdelimiter)); //Maybe -2 *sizeof(char) because we won't have 3 \0
    
    //Building of the first element
    (void) stpcpy(gerlist, mywordpair->german);
    (void) strcat(gerlist, delimiter);
    (void) strcat(gerlist, mywordpair->english);
    (void) strcat(gerlist, pairdelimiter);
    
    //and the possible rest
    tobelisted->gerList->current = tobelisted->gerList->head;
    while (tobelisted->gerList->current->next != NULL) {
        mywordpair = getNext(tobelisted->gerList);
        
        gerlist = realloc(gerlist, sizeof(gerlist)
                + sizeof(mywordpair->german) + sizeof(delimiter) + sizeof(mywordpair->english) +sizeof(pairdelimiter));
        if (gerlist == NULL) {
            return NULL;
        }
        
        (void) strcat(gerlist, mywordpair->german);
        (void) strcat(gerlist, delimiter);
        (void) strcat(gerlist, mywordpair->english);
        (void) strcat(gerlist, pairdelimiter);
    }
    return gerlist;
}
char* getSortedListEnglish(const vocalist *tobelisted)
{
    char *englist; //Momomo-Monster listlistlist... Todo But how to free?!
    const char delimiter[] = {" "};
    const char pairdelimiter[] = {"\n"};
    
    if (getFirst(tobelisted->engList) == NULL) {
        return NULL;
    }
    
    //Allocating of the first element
    wordpair *mywordpair = (wordpair *) getFirst(tobelisted->engList);
    
    englist = malloc(sizeof(mywordpair->english) + sizeof(delimiter) + sizeof(mywordpair->german) + sizeof(pairdelimiter)); //Maybe -2 *sizeof(char) because we won't have 3 \0
    
    //Building of the first element
    (void) stpcpy(englist, mywordpair->english);
    (void) strcat(englist, delimiter);
    (void) strcat(englist, mywordpair->german);
    (void) strcat(englist, pairdelimiter);
    
    //and the possible rest
    tobelisted->engList->current = tobelisted->engList->head;
    while (tobelisted->engList->current->next != NULL) {
        mywordpair = getNext(tobelisted->engList);
        
        englist = realloc(englist, sizeof(englist)
                          + sizeof(mywordpair->english) + sizeof(delimiter) + sizeof(mywordpair->german) +sizeof(pairdelimiter));
        if (englist == NULL) {
            return NULL;
        }
        
        (void) strcat(englist, mywordpair->english);
        (void) strcat(englist, delimiter);
        (void) strcat(englist, mywordpair->german);
        (void) strcat(englist, pairdelimiter);
    }
    return englist;
}



