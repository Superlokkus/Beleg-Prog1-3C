//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: XXXXX
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
    if (pList->current == NULL) {//Invalid call
        return;
    }
    if (pList->current == pList->head && pList->current == pList->tail) {
        //Last item in list
        free(pList->current);
        pList->current = NULL; pList->head = NULL; pList->tail = NULL;
        return; //There should not be a need to handle this elsewhere
    }
    
    if (pList->current == pList->head) {
        pList->current->next->prev = NULL;
        pList->head = pList->current->next;
    }
    else if (pList->current == pList->tail) {
        pList->current->prev->next = NULL;
        pList->tail = pList->current->prev;
    }
    else
    {
        pList->current->next->prev = pList->current->prev;
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
    if (pList->current == NULL || pList->current->next == NULL) {
        return NULL;
    }
    pList->current = pList->current->next;
    return pList->current->item;
}
void* getPrev(tList* pList)
{
    if (pList->current == NULL || pList->current->prev == NULL) {
        return NULL;
    }
    pList->current = pList->current->prev;
    return pList->current->item;
}
void* getIndexed(tList* pList,int Idx)
{
    if (Idx >= 0) {
        pList->current = pList->head;
        int i;
        for (i=0; i<Idx; i++) {
            pList->current = pList->current->next;
            if (pList->current == NULL) {
                return NULL;
            }
        }
    }
    else //Begin at tail Idx <0
    {
        pList->current = pList->tail;
        int i;
        for (i=0; i>Idx; i--) {
            pList->current = pList->current->prev;
            if (pList->current == NULL) {
                return NULL;
            }
        }
    }
    return pList->current->item;
}
int addItemToList (tList* pList,void * pItem,int(*fcmp)(void*pItList,void*pItNew))
{
    //List empty?
    if (pList->head == NULL) {
        insertHead(pList, pItem);
        return OK;
    }
    
    //Corner cases
    if (fcmp(pItem,getFirst(pList)) <= 0) {
        if (insertHead(pList, pItem) == OK)
            return OK;
        else
            return FAIL;
    }
    if (fcmp(pItem,getLast(pList)) > 0) {
        if (insertTail(pList, pItem) == OK)
            return OK;
        else
            return FAIL;
    }
    //End corner cases (head needed, tail for optimization)
    
    pList->current = pList->head;
    while (fcmp(pItem,getNext(pList)) >0);
    if (insertBefore(pList, pItem) != OK) {
        return FAIL;
    }
    return OK;
}


