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

int insertHead (tList* pList, void *pItemIns)
{
    if (pList->head == NULL) {
        tCnct *newCnct = malloc(sizeof(tCnct));
        if (newCnct == NULL) {
            return FAIL;
        }
        newCnct->item = pItemIns;
        pList->head = newCnct; pList->tail = newCnct; pList->current = newCnct;
        return OK;
    }
    //(else)
    tCnct * maybesomebodywantstousecurrent = pList->current;
    
    pList->current = pList->head;
    
    if (insertBefore(pList, pItemIns) != OK) {
        pList->current = maybesomebodywantstousecurrent;
        return FAIL;
    }
    pList->current = maybesomebodywantstousecurrent;
    return OK;
}

int insertTail (tList* pList, void *pItemIns)
{
    if (pList->head == NULL) {
        tCnct *newCnct = malloc(sizeof(tCnct));
        if (newCnct == NULL) {
            return FAIL;
        }
        newCnct->item = pItemIns;
        pList->head = newCnct; pList->tail = newCnct; pList->current = newCnct;
        return OK;
    }
    //(else)
    tCnct * maybesomebodywantstousecurrent = pList->current;
    pList->current = pList->tail;
    
    if (insertBehind(pList, pItemIns) != OK) {
        pList->current = maybesomebodywantstousecurrent;
        return FAIL;
    }
    pList->current = maybesomebodywantstousecurrent;
    return OK;

}

void removeItem(tList* pList)
{
    if (pList->current == NULL) {
        return;
    }
    if (pList->current == pList->head && pList->current == pList->tail) {
        //Last item in list
        free(pList->current);
        pList->current = NULL; pList->head = NULL; pList->tail = NULL; //There should not be a need to handle this elsewhere
    }
    
    if (pList->current == pList->head) {
        pList->current->next->prev = NULL;
        pList->head = pList->current->next;
    }
    else
    {
        pList->current->next->prev = pList->current->prev;
    }
    if (pList->current == pList->tail) {
        pList->current->prev->next = NULL;
        pList->tail = pList->current;
    }
    else
    {
        pList->current->prev->next = pList->current->next;
    }
    
    free(pList->current);
    pList->current = NULL;
}
void* getSelected(tList* pList)
{
    if (pList->current == NULL) {
        return NULL; //You get what you deserve
    }
    return pList->current->item;
}
void* getFirst(tList* pList)
{
    if (pList->head == NULL) {
        return NULL;
    }
    return pList->head->item;
}
void* getLast(tList* pList)
{
    if (pList->tail == NULL) {
        return NULL;
    }
    return pList->tail->item;
}
void* getNext(tList* pList)
{
    if (pList->current == NULL) {
        return NULL;
    }
    pList->current = pList->current->next;
    return pList->current->item;
}
void* getPrev(tList* pList)
{
    if (pList->current == NULL) {
        return NULL;
    }
    pList->current = pList->current->prev;
    return pList->current->item;
}
void* getIndexed(tList* pList,int Idx)
{
    pList->current = pList->head;
    int i;
    for (i=0; i<Idx; i++) {
        /*Loop could be avioded with current = current + Idx
         but in that case, behaviour for Idx > n Elements would be undefined*/
        if (pList->current->next == NULL && i != Idx-1) {
            return NULL;
        }
        pList->current++;
    }
    return pList->current->item;
}

