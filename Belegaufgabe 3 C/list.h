//Name: Markus Klemm
//Studiengruppe: 13/041/01
//MatrNr: 36438
///
/*! @file list.h
 @Library for a double linked list
 @author Markus Klemm
*/

#ifndef MKN_Beleg3C_list_h
#define MKN_Beleg3C_list_h

/* @typedef
 @brief Representation of a node in a tList.
 @privatesection
 */
typedef struct tCnct
{
    struct tCnct * prev; //< == NULL if head
    struct tCnct * next; //< == NULL if tail
    void * item;
    
}tCnct;	/* Datentyp fuer Connector */

/*! @typedef
 @brief Representation of a double linked list.
 
 @public
*/
typedef struct
{
    tCnct * head; //!< ==NULL if empty
    tCnct * current; //!< To be manipulated by user. ==NULL if empty
    tCnct * tail; //!< ==NULL if empty
}tList;	/* Datentyp fuer die Liste */

#define OK 1
#define FAIL 0

/*!
 @brief Creates an empty list. 
 
 Head, tail and current are initialised to NULL.
 @returns Returns NULL if allocation fails, else the new tList.
 */
tList * createList(void);
/*!
 @brief Deletes an empty list.
 @param pList The tList which should be deleted.
 @return Returns FAIL if list is not empty, else OK.
 */
int     deleteList(tList* pList);

int    insertBehind  (tList* pList, void *pItemIns);/* fuege ein hinter %  */
int    insertBefore  (tList* pList, void *pItemIns);/* fuege ein vor    %  */
int    insertHead    (tList* pList, void *pItemIns);//Won't change current /* fuege vorn ein      */
int    insertTail    (tList* pList, void *pItemIns);//Won't change current /* fuege hinten ein    */
/*! @brief Add Item to a sorted/empty List.
 @returns #OK if adding was sucessfull, else #FAIL
 @attention Only use this function and deleteList() for item manipulation, to sustain an ordered list.
 @param *pList And already sorted or empty List.
 @param *pItem Pointer to item to add.
 @param (*fcmp) Function for the sorting criteria, which must returns a integer of the comparsion like strcmp() does.
 */
int    addItemToList (tList* pList,
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
