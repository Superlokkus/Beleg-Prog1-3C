//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
#ifndef MKN_Beleg3C_list_h
#define MKN_Beleg3C_list_h

/* list.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

typedef struct tCnct
{
    struct tCnct * prev; //== NULL if head
    struct tCnct * next; //== NULL if tail
    void * item;
    
}tCnct;	/* Datentyp fuer Connector */

typedef struct
{
    tCnct * head; //==NULL if empty
    tCnct * current; //==NULL if empty
    tCnct * tail; //==NULL if empty
    unsigned long elements;
}tList;	/* Datentyp fuer die Liste */

#define OK 1
#define FAIL 0
/*-------------------------------------------------------------------------*/
/* Prototypen fuer die Funktionen                                          */

/* list.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

tList * createList(void);//Returns NULL if something fails  /* erzeuge leere Liste */
int     deleteList(tList* pList);                   /* loesche leere Liste */

int    insertBehind  (tList* pList, void *pItemIns);/* fuege ein hinter %  */
int    insertBefore  (tList* pList, void *pItemIns);/* fuege ein vor    %  */
int    insertHead    (tList* pList, void *pItemIns);//Won't change current /* fuege vorn ein      */
int    insertTail    (tList* pList, void *pItemIns);//Won't change current /* fuege hinten ein    */
int    addItemToList (tList* pList, //Assumes pList is already sorted		    /* fuege sortiert ein  */
                     void * pItem,
                     int(*fcmp)(void*pItList,void*pItNew));

void   removeItem    (tList* pList);//Sets current to NULL                /* loesche %           */

void* getSelected    (tList* pList);                /* gib aktuellen DS    */
void* getFirst       (tList* pList);//Won't change current                /* gib ersten DS       */
void* getLast        (tList* pList);//Won't change current               /* gib letzten DS      */
void* getNext        (tList* pList);                /* gib naechsten DS    */
void* getPrev        (tList* pList);                /* gib vorigen DS      */
void* getIndexed     (tList* pList, //returns NULL for invalid Idx
                      int Idx);//Negative Idx for reverse beginning at tail   /* gib DS lt. Index    */
#endif //MKN_Beleg3C_list_h
