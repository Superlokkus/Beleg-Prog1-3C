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
    
    return strcmp(wfirst->german, wsecond->german);
}
int engCmp(void *first,void *second)
{
    const wordpair *wfirst = (const wordpair *)first;
    const wordpair *wsecond = (const wordpair *)second;
    
    return strcmp(wfirst->english, wsecond->english);
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
    if (strcmp(getFirst(list->gerList), german) == 0) {
        return getFirst(list->gerList);
    }

    while(true) { //Infinite loop danger
        if (getNext(list->gerList) == NULL) {
            return NULL;
        }
        wordpair *mywordpair = (wordpair *) getSelected(list->gerList);
        if(strcmp(mywordpair->german, german) == 0)
            return mywordpair->english;
    }
}

