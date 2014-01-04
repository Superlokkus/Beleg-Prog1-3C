//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
//
//  list.c
//  Belegaufgabe 3 C
//
//  Created by Markus Klemm on 03.01.14.
//  Copyright (c) 2014 Markus Klemm Enterprises. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "list.h"


tList * createList(void)
{
    tList *newList = malloc(sizeof(tList));
    if (newList == NULL) {
        return NULL;
    }
    newList->head = NULL;
    newList->current = NULL;
    newList->tail = NULL;
    
    return newList;
}

int deleteList(tList* pList)
{
    if (pList->head == NULL)
    {
        free(pList);
        return OK;
    }
    return FAIL;
}

int insertBehind(tList* pList, void *pItemIns)
{
    if (pList->current == NULL) {
        return FAIL; //Empty list?!
    }
    
    tCnct *newCnct = malloc(sizeof(tCnct));
    if (newCnct == NULL) {
        return FAIL;
    }
    newCnct->item = pItemIns;
    
    
    newCnct->prev = pList->current;
    
    if (pList->current == pList->tail) {
        newCnct->next = NULL;
        pList->tail = newCnct;
    }
    else
    {
    newCnct->next = pList->current->next;
    pList->current->next->prev = newCnct;
    }
    
    pList->current->next = newCnct;
    pList->current = newCnct;
    
    return OK;
}

int insertBefore(tList* pList, void *pItemIns)
{
    if (pList->current == NULL) {
        return FAIL;
    }
    
    tCnct *newCnct = malloc(sizeof(tCnct));
    if (newCnct == NULL) {
        return FAIL;
    }
    newCnct->item = pItemIns;
    
    newCnct->next = pList->current;
    
    if (pList->current == pList->head) {
        newCnct->prev = NULL;
        pList->head = newCnct;
    }
    else
    {
        newCnct->prev = pList->current->prev;
        pList->current->prev->next = newCnct;
    }
    
    pList->current->prev = newCnct;
    pList->current = newCnct;
    
    return OK;
}


