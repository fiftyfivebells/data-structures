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
    list->blockSize = blockSize+1;

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
    if (list->dummy->next == NULL && list->dummy->prev == NULL)  {
	Node *newNode = makeNewNode(list->blockSize);
	list->dummy->next = newNode;
	list->dummy->prev = newNode;
    }

    Node *head = list->dummy->next;

    addToFront(data, head->deque);

}

void addTail(int data, SELList *list) {

    // if there are no nodes in the list, add one
    if (list->dummy->next == NULL && list->dummy->prev == NULL)  {
	Node *newNode = makeNewNode(list->blockSize);
	list->dummy->next = newNode;
	list->dummy->prev = newNode;
    }
    
    Node *tail = list->dummy->prev;

    addToBack(data, tail->deque);
}

void SELLaddToIndex(int i, int data, SELList *list) {
    
}

/**
 * List Utility Methods:
 * printList
 */
Node * makeNewNode(int blockSize) {
    Node *toAdd = malloc(sizeof(Node));
    toAdd->deque = newBoundedDeque(blockSize);

    return toAdd;
}

Location * getLocation(int i, SELList *list) {
    Node *current = list->dummy->next;
    Location *l = malloc(sizeof(Location));

    while(current != NULL && i > current->deque->size) {
	i -= current->deque->size;
	current = current->next;
    }

    l->node = current;
    l->index = i;

    return l;
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

