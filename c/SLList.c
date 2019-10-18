#include <stdio.h>
#include <stdlib.h>
#include "SLList.h"


/**
 * Add methods:
 * addNode adds a new node at any index in the list
 * addHead adds a new node at the head of the list
 * addTail adds a new node at the tail of the list
 */
void addNode(int i, int data, SLList *list) {
    int      currPos = 0;  // our current position in the list
    SLNode  *current = list->head;  // current node is the head of the list
    SLNode *previous = NULL;

    // if index is 0, add to the head
    if (i == 0) {
	addHead(data, list);
	return;
    }

    // if index is the last thing in the list, add to the tail
    if (i == list->size) {
	addTail(data, list);
    }

    SLNode *newNode = makeNode(data);

    while(current != NULL) {
	if (currPos == i) break;
	
	previous = current;
	current = current->next;
	currPos++;
    }

    // set the new node's next pointer to the current node
    newNode->next = current;

    // then update the previous node's next to point at the new node
    previous->next = newNode;

    // increase the size of the list
    list->size++;
}

void addHead(int data, SLList *list) {
    SLNode *current = list->head;
    SLNode *newNode = makeNode(data);

    // set the new node's next pointer to the current head of the list
    newNode->next = current;

    // set the singly-linked list's head to the new node
    list->head = newNode;

    // make sure the tail gets set if this is the first element
    if (list->size == 0)
	list->tail = newNode;

    // increase the size of the list
    list->size++;
}

void addTail(int data, SLList *list) {
    SLNode *current = list->tail;
    SLNode *newNode = makeNode(data);

    // set the current tail's next to the new node
    current->next = newNode;

    // update the list's tail to the new node
    list->tail = newNode;

    // make sure the head gets set if this is the first element
    if (list->size == 0)
	list->head = newNode;

    // increase the size of the list
    list->size++;
}

/**
 * Remove Methods:
 * removeNode takes the node out of the given index and returns the data
 * removeHead takes the head off of the list and returns its value
 * removeTail takes the tail off and returns the value there
 */


// allocates memory for a new SLNode, sets its data, initializes its pointer to
// NULL, and then returns a pointer to the new node
SLNode* makeNode(int data) {

    SLNode *newNode = malloc(sizeof(SLNode));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void printList(SLList *list) {

    SLNode *current = list->head;

    while (current != NULL) {
	printf("[%d] --> ", current->data);

	current = current->next;

	if (current == NULL)
	    printf("NULL\n");
    }
}

