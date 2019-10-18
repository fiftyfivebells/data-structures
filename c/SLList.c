#include <stdio.h>
#include <stdlib.h>
#include "SLList.h"


/**
 * Get/Set Methods:
 * get walks to a specific node and returns the data that was there
 * set walks to a specific node and changes the data that was there
 */
int getNode(int i, SLList *list) {
    int      currPos = 0;           // our current position in the list
    SLNode  *current = list->head;  // current node is the head of the list

    // if we're getting from the tail, just use the tail reference
    if (i == list->size - 1)
	return list->tail->data;

    // otherwise walk down the list to the item we want
    while (currPos != i) {
	if (currPos == i) break;

	current = current->next;
    }

    return current->data;
}

int getHead(SLList *list) {
    return getNode(0, list);
}

int getTail(SLList *list) {
    return getNode(list->size - 1, list);
}

void setNode(int i, int data, SLList *list) {
    int      currPos = 0;           // our current position in the list
    SLNode  *current = list->head;  // current node is the head of the list

    // if we're setting the tail, just use the tail reference
    if (i == list->size - 1)
	list->tail->data = data;

    // otherwise we walk down the list looking for the index
    else {
	while (currPos != i) {
	    if (currPos == i) break;

	    current = current->next;
	}

	// set the node's data to the new data
	current->data = data;
    }
}

void setHead(int data, SLList *list) {
    setNode(0, data, list);
}

void setTail(int data, SLList *list) {
    setNode(list->size - 1, data, list);
}

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

// takes an index and SLList, removes the node at the index, frees it, and returns the data
int removeNode(int i, SLList *list) {

    // if i is zero, we're removing from head, so delegate to that function
    if (i == 0)
	return removeHead(list);

    // if i is the last thing in the list, delegate to removeTail
    if (i == list->size-1)
	return removeTail(list);

    SLNode  *current = list->head;
    SLNode *previous = NULL;
    int      currPos = 0;

    while (current != NULL) {
	if (currPos == i) break;

	previous = current;
	current = current->next;
	currPos++;
    }

    // this is the data being returned from the function
    int data = current->data;

    // set the previous node's next pointer to the node after current
    previous->next = current->next;

    // then free the current node to deallocate the memory
    free(current);

    list->size--;

    return data;
}

// takes in a SLList, frees the head, then returns the data
int removeHead(SLList *list) {
    SLNode *current = list->head;
    int data = current->data;

    // set the head to the next thing in the list
    list->head = current->next;

    // then free the old head
    free(current);

    // decrease the size of the list
    list->size--;

    return data;
}

// takes in the SLList, frees the tail, then returns the data
int removeTail(SLList *list) {
    SLNode  *current = list->head;
    SLNode *previous = NULL;

    // unfortunately, having a reference to the tail doesn't help remove it, we
    // still need to walk to the one before it to set the tail after removal
    while (current->next != NULL) {
	previous = current;
	current = current->next;
    }

    int data = current->data;

    // set the previous node's next to NULL, since it's now last in the list
    previous->next = NULL;

    // set the list's tail to the previous node
    list->tail = previous;

    // then free up the now removed node
    free(current);

    list->size--;

    return data;
}

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

