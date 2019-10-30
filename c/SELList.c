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
    list->dummy->prev = list->dummy;
    list->dummy->next = list->dummy;

    return list;
}

/**
 * Add functions
 */
void addHead(int data, SELList *list) {

    // if there are no nodes in the list, add one
    if (list->dummy->next == NULL && list->dummy->prev == NULL)  {
	Node *newNode = makeNewNode(list->blockSize+1);
	list->dummy->next = newNode;
	list->dummy->prev = newNode;
    }

    Node *head = list->dummy->next;

    addToFront(data, head->deque);
}

void addTail(int data, SELList *list) {

    Node *last = list->dummy->prev;

    // if the last node in the list is the dummy or it's full, make a new node
    if (last == list->dummy || last->deque->size == list->blockSize+1) {
	last = addBeforeNode(list->dummy, list->blockSize+1);
    }

    // and now add to the back of the last node in the list
    addToBack(data, last->deque);
    list->size++;
}

void SELLaddToIndex(int i, int data, SELList *list) {
    
}

/**
 * List Utility Methods:
 * printList
 */
void spread(Node *node, int blockSize) {
    Node *current = node;

    for (int i = 0; i < blockSize; i++) {
	current = current->next;
    }
    current = addBeforeNode(current, blockSize);

    while (current != node) {
	while (current->deque->size < blockSize) {
	    addToFront(removeFromBack(current->prev->deque), current->deque);
	}
	current = current->prev;
    }
}

Node * addBeforeNode(Node *node, int blockSize) {
    Node *newNode = makeNewNode(blockSize);

    // set the newNode's next and prev pointers
    newNode->prev = node->prev;
    newNode->next = node;

    node->prev->next = newNode;
    node->prev = newNode;

    return newNode;
}

Node * makeNewNode(int blockSize) {
    Node *toAdd = malloc(sizeof(Node));
    toAdd->deque = newBoundedDeque(blockSize);

    return toAdd;
}

Location * getLocation(int i, SELList *list) {
    Node *current;
    Location *l = malloc(sizeof(Location));

    // if in front half of list, start at the front and work in
    if (i <= list->size/2) {
	current = list->dummy->next;
	while(i > current->deque->size) {
	    i -= current->deque->size;
	    current = current->next;
	}

	l->node = current;
	l->index = i;
    }

    // otherwise, start at the back and work back
    else {
	current = list->dummy;
	int index = list->size;

	while (index > i) {
	    index -= current->deque->size;
	    current = current->prev;
	}
	l->node = current;
	l->index = i - index;
    }
    
    return l;
}

void printList(SELList *list) {
    Node *head = list->dummy;

    printf("[");
    while (head->next != list->dummy) {
	printDeque(head->next->deque);
	if (head->next->next != list->dummy)
	    printf(" -> ");
	head = head->next;
    }
    printf("]\n");
}

