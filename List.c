/*
 *  List.c
 *  Implementation file for List ADT
 */

#include<stdio.h>
#include<stdlib.h>

#include "List.h"

/************** Private Structs: not exported *************************************/

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef Node* NodeRef;

typedef struct List {
    NodeRef front;
    NodeRef back;
    NodeRef current;
    int length;
} List;
/************** Constructors-Destructors ******************************************/

/*  newList
 *  Returns ListRef pointing to new ListSturct which represents an empty List.
 *  Initializes front and back fields to NULL, sets length field to 0.  
 *  Exported.
 */
ListRef newList(void) {
    ListRef L;
    L = malloc(sizeof (List));
    L->front = L->back = L->current = NULL;
    L->length = 0;
    return (L);
}

/*  newNode
 *  Returns pointer to new Node struct. Initializes next field to NULL, and sets
 *  data field to input parameter node_data. 
 * Private.
 */
NodeRef newNode(int node_data) {
    NodeRef N = malloc(sizeof (Node));
    N->data = node_data;
    N->next = NULL;
    N->prev = NULL;
    return (N);
}

/*  freeNode
 *  Frees heap memory pointed to by pN. 
 * Private.
 */
void freeNode(NodeRef* pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

/*  freeList
 *  Frees all heap memory associated with the ListRef *pL, including all memory
 *  in existing Nodes.  Sets *pL to NULL.  Exported.
 */
void freeList(ListRef* pL) {
    if (pL != NULL && *pL != NULL) {
        while (!isEmpty(*pL)) {
            deleteBack(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
/***************** Access functions ***********************************************/

/*  getLength
 *  Returns the length of L
 */
int getLength(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getLength() on NULL ListRef\n");
        exit(1);
    }
    return L->length;
}

/*  isEmpty
 *  Returns True if L is empty, otherwise returns 0
 */
int isEmpty(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling isEmpty() on NULL ListRef\n");
        exit(1);
    }
    return (L->front == NULL);
}

/* offEnd
 * Returns True if current is undefined
 */
int offEnd(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling offEnd() on NULL ListRef\n");
        exit(1);
    }
    return (L->current == NULL);
}

/* getIndex
 * Returns current index. If Current is not defined, return -1.
 * Pre: defined List
 */
int getIndex(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getIndex() on NULL ListRef\n");
        exit(1);
    }

    if (L->current == NULL) {
        return -1;
    }

    NodeRef M = L->front;
    int position = 0;
    while (M != L->current) {
        M = M->next;
        position++;
    }
    return position;
}

/*  getFront
 *  Returns the value at the front of L.
 *  Pre: !isEmpty(L)
 */
int getFront(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getFront() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling getFront() on an empty List\n");
        exit(1);
    }
    return (L->front->data);
}

/* getBack
 * Returns the value at the back of L
 * Pre: !isEmpty(L), !(null list)
 */
int getBack(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getBack) on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling getBack() on an empty List\n");
        exit(1);
    }
    return (L->back->data);
}

/* getCurrent
 * returns the value at the current node of L
 * Pre: !isEmpty(L), !(null list)
 */
int getCurrent(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling getCurrent() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling getCurrent() on an empty List\n");
        exit(1);
    }
    if (offEnd(L)) {
        printf("List Error: calling getCurrent() on offEnd current\n");
        exit(1);
    }
    return (L->current->data);
}

/* equals
 * Returns true is list A equals list B
 * Pre: !(null list)
 */
int equals(ListRef A, ListRef B) {
    int flag = 1;
    Node* N = NULL;
    Node* M = NULL;

    if (A == NULL || B == NULL) {
        printf("List Error: calling equals() on NULL ListRef\n");
        exit(1);
    }
    N = A->front;
    M = B->front;
    if (A->length != B->length) {
        return 0;
    }
    while (flag && N != NULL) {
        flag = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return flag;
}

/**************** Manipulation procedures ****************************************/

/* makeEmpty
 * Deletes all the nodes in the list
 * Pre: !(null list)
 * 
 */
void makeEmpty(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling makeEmpty() on NULL ListRef\n");
        exit(1);
    }
    while (L->front != NULL) {
        deleteBack(L);
    }
}

/* moveTo
 * Moves current node to new index position
 * Pre: !isEmpty(L), !(null list), !offEnd
 */
void moveTo(ListRef L, int i) {
    if (L == NULL) {
        printf("List Error: calling moveTo() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling moveTo() on an empty List\n");
        exit(1);
    }

    L->current = L->front;
    int pos;
    if (0 <= i || i <= (getLength(L) - 1)) {
        for (pos = 0; pos < i; pos++) {
            moveNext(L);
        }
    } else {
        L->current = NULL;
        printf("List Error: Moving to out of bounds area.\n");
    }
}

/* movePrev
 * Moves current index to previous node
 * Pre: !isEmpty(L), !(null list)
 */
void movePrev(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling movePrev() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling movePrev() on an empty List\n");
        exit(1);
    }
    L->current = L->current->prev;
}

/* moveNext
 * Moves current index to next node
 * Pre: !isEmpty(L), !(null list)
 */
void moveNext(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling moveNext() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling moveNext() on an empty List\n");
        exit(1);
    }
    L->current = L->current->next;
}

/* insertFront
 * Insets an element to the front of the list
 * Pre: !(null list)
 */
void insertFront(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling EnList() on NULL ListRef\n");
        exit(1);
    }
    NodeRef N = newNode(data);
    if (isEmpty(L)) {
        L->front = L->back = N;
    } else {
        N->prev = NULL;
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
    }
    L->length++;
}

/* insertBack
 * Inserts an element to the back of the list
 * Pre: !(null list)
 */
void insertBack(ListRef L, int data) {
    if (L == NULL) {
        printf("List Error: calling insertBack() on NULL ListRef\n");
        exit(1);
    }
    NodeRef N = newNode(data);
    if (isEmpty(L)) {
        L->front = L->back = N;
    } else {
        N->next = NULL;
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
    }
    L->length++;
}

/* insertBeforeCurrent
 * Insert an element before the current element
 * Pre: !(null list), !offEnd, !isEmpty
 */
void insertBeforeCurrent(ListRef L, int data) {
    if (L->current == NULL) {
        printf("List Error: calling insertBeforeCurrent() on offEnd ListRef\n");
        exit(1);
    }
    if (L == NULL) {
        printf("List Error: calling insertBeforeCurrent() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling insertBeforeCurrent() on Empty ListRef\n");
        exit(1);
    }
    NodeRef N = newNode(data);
    /*we use this if statement so the value front will be accurate*/
    if (L->current == L->front) {
        N->prev = NULL;
        L->current->prev = N;
        N->next = L->current;
        L->front = N;
    } else {
        N->prev = L->current->prev;
        L->current->prev->next = N;
        L->current->prev = N;
        N->next = L->current;

    }
    L->length++;

}

/* insertAfterCurrent
 * Insert an element after the current element
 * Pre: !(null list), !offEnd, !isEmpty
 */
void insertAfterCurrent(ListRef L, int data) {
    if (L->current == NULL) {
        printf("List Error: calling insertBeforeCurrent() on offEnd ListRef\n");
        exit(1);
    }
    if (L == NULL) {
        printf("List Error: calling insertBeforeCurrent() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling insertBeforeCurrent() on Empty ListRef\n");
        exit(1);
    }
    NodeRef N = newNode(data);
    /*we use this if statement so the value back will be accurate*/
    if (L->current == L->back) {
        N->next = NULL;
        L->current->next = N;
        N->prev = L->current;
        L->back = N;

    } else {
        N->next = L->current->next;
        L->current->next->prev = N;
        L->current->next = N;
        N->prev = L->current;

    }
    L->length++;

}

/*  deleteFront
 *  Deletes element at the front of the list
 *  Pre: !isEmpty(L)
 */
void deleteFront(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    NodeRef N = L->front;
    if (L->current == L->front) {

        L->current = NULL;
    }
    if (L->length > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else if (L->length == 1) {
        L->front = L->back = NULL;
    }

    L->length--;
    freeNode(&N);

}

/*  deleteBack
 *  Deletes element at the back of the list
 *  Pre: !isEmpty(L)
 */
void deleteBack(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    NodeRef N = L->back;
    if (L->current == L->back) {
        L->current = NULL;
    }

    if (L->length > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else if (L->length == 1) {
        L->back = L->front = NULL;
    }

    L->length--;
    freeNode(&N);
}

/*  deleteCurrent
 *  Deletes element at current position of the list
 *  Pre: !isEmpty(L), !offEnd
 */
void deleteCurrent(ListRef L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL ListRef\n");
        exit(1);
    }
    if (isEmpty(L)) {
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(1);
    }
    if (offEnd(L)) {
        printf("List Error: Calling deleteCurrent() on an offEnd List\n");
    }
    NodeRef N = L->current;
    if (L->current == L->front) {
        deleteFront(L);
    } else if (L->current == L->back) {
        deleteBack(L);
    } else {
        L->current->prev->next = L->current->next;
        L->current->next->prev = L->current->prev;
        L->current = NULL;
        L->length--;
        freeNode(&N);
    }

}

/*************** Other Functions *************************************************/

/*  printList
 *  Prints data elements in L on a single line to stdout.
 */
void printList(FILE* out, ListRef L) {
    if (L == NULL) {
        printf("List Error: calling printList() on NULL ListRef\n");
        exit(1);
    }

    Node* N = NULL;

    for (N = L->front; N != NULL; N = N->next) {

        if (N == L->back)
            fprintf(out,"%d", N->data);
        else
            fprintf(out,"%d ", N->data);



    }


}

ListRef copyList(ListRef L) {

    /*creates a new list that will need to be freed later*/
    ListRef C = newList();
    NodeRef N = L->front;
    int i;
    for (i = 0; i < getLength(L); i++) {
        insertBack(C, N->data);
        N = N->next;
    }
    C->current = NULL;
    return C;
}

