/*
 *  List.h
 *  Header file for List ADT
 */
#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_


/***************************** Exported Types *************************************/
typedef struct List* ListRef;
/* Recall: typedef is a keyword in C that assigns alternative names to existing types
 * 
 */

/************** Constructors-Destructors ******************************************/

ListRef newList(void);
/*  newList
 *  Returns ListRed pointing to new ListSturct which represents an empty List.
 *  Initializes front and back fields to NULL, sets length field to 0.  Exported.
 */

void freeList(ListRef* pL);
/*  freeList
 *  Frees all heap memory associated with the ListRef *pL, including all memory
 *  in existing Nodes.  Sets *pL to NULL.  Exported.
 */

/***************** Access functions ***********************************************/

int getLength(ListRef L);
/*  getLength
 *  Returns the length of L
 */

int isEmpty(ListRef L);
/*  isEmpty
 *  Returns True if L is empty, otherwise returns false
 */

int offEnd(ListRef L);
/*
 * 
 */

int getIndex(ListRef L);
/*
 * 
 */

int getFront(ListRef L);
/*  getFront
 *  Returns the value at the front of L.
 *  Pre: !isEmpty(L)
 */

int getBack(ListRef L);
/*
 * 
 */

int getCurrent(ListRef L);
/*
 * 
 */

int equals(ListRef A, ListRef B);
/*
 * 
 */

/****************************** Manipulation procedures ***************************/
void makeEmpty(ListRef L);
/*
 * 
 */

void moveTo(ListRef L, int i);
/*
 * 
 */

void movePrev(ListRef L);
/*
 * 
 */

void moveNext(ListRef L);
/*
 * 
 */

void insertFront(ListRef L, int data);
/*
 * 
 */

void insertBack(ListRef L, int data);
/*  InsertBack
 *  Places new data element at the end of L
 *  Post: !isEmpty(L)
 */

void insertBeforeCurrent(ListRef L, int data);
/*
 * 
 */

void insertAfterCurrent(ListRef L, int data);
/*
 * 
 */

void deleteFront(ListRef L);
/*  deleteFront
 *  Deletes element at front of L
 *  Pre: !isEmpty(L)
 */

void deleteBack(ListRef L);
/*
 * 
 */

void deleteCurrent(ListRef L);
/*
 * 
 */

/*************** Other Functions *************************************************/


void printList(FILE* out, ListRef L);
/*  printList
 *  Prints data elements in L on a single line to stdout.
 */

ListRef copyList(ListRef L);
/*  equals
 *  returns true if A is identical to B, false otherwise
 */

#endif
