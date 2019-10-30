#include <stdio.h>
#include <stdlib.h>
#include "SELList.h"

/**
 * Initializes a new Space-Efficient Linked List
 */
SELList * newSELList(int blockSize) {
    
    SELList *list = malloc(sizeof(SELList));

    list->dummy = malloc(sizeof(Node));
    list->size = 0;
    list->blockSize = blockSize;

    // set the dummy's prev and next to null
    list->dummy->prev = NULL;
    list->dummy->next = NULL;

    return list;
}

/**
 * Add functions
 */
void addHead(int data, SELList *list) {

    // if there are no nodes in the list, add one
    if (list->dummy->next == NULL) {
	list->dummy->next = malloc(sizeof(Node));
	list->dummy->next->deque = newBoundedDeque(list->blockSize);
    }

    Node *head = list->dummy->next;

    addToFront(data, head->deque);

}

/**
 * List Utility Methods:
 * printList
 */
Node * addNewNodeToList(Node *prev, Node *next, int blockSize) {

    Node *toAdd = malloc(sizeof(Node));
    toAdd->deque = newBoundedDeque(blockSize);

    // set the new node's next and prev pointers to the two provided nodes
    toAdd->next = next;
    toAdd->prev = prev;

    // if the prev and next node's aren't null, set their pointers
    if (prev != NULL)
	prev->next = toAdd;

    if (next != NULL)
	next->prev = toAdd;

    return toAdd;
}

void printList(SELList *list) {
    Node *head = list->dummy;

    printf("[");
    while (head->next != NULL) {
	printDeque(head->next->deque);
	head = head->next;
    }
    printf("]\n");
}

