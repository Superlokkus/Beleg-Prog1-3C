/*  bitte in alle Quellfiles eintragen! 
Name:
Studiengruppe:
MatrNr:
*/


/* list.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

typedef . . . tCnct;	/* Datentyp fuer Connector */

typedef . . . tList;	/* Datentyp fuer die Liste */

#define OK 1
#define FAIL 0
/*-------------------------------------------------------------------------*/
/* Prototypen fuer die Funktionen                                          */

/* list.h */
/*------------------------------------------------------------------------*/
/* Datenstruktur eines Listenverbindungselementes                         */

tList * createList(void);                           /* erzeuge leere Liste */
int     deleteList(tList* pList);                   /* loesche leere Liste */

int    insertBehind  (tList* pList, void *pItemIns);/* fuege ein hinter %  */
int    insertBefore  (tList* pList, void *pItemIns);/* fuege ein vor    %  */
int    insertHead    (tList* pList, void *pItemIns);/* fuege vorn ein      */
int    insertTail    (tList* pList, void *pItemIns);/* fuege hinten ein    */
int    addItemToList (tList* pList, 		    /* fuege sortiert ein  */
                     void * pItem,
                     int(*fcmp)(void*pItList,void*pItNew));

void   removeItem    (tList* pList);                /* loesche %           */

void* getSelected    (tList* pList);                /* gib aktuellen DS    */
void* getFirst       (tList* pList);                /* gib ersten DS       */
void* getLast        (tList* pList);                /* gib letzten DS      */
void* getNext        (tList* pList);                /* gib naechsten DS    */
void* getPrev        (tList* pList);                /* gib vorigen DS      */
void* getIndexed     (tList* pList,int Idx);        /* gib DS lt. Index    */
