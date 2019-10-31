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
 
   if (i < 0 || i > list->size) {
	printf("Index %d is out of bounds.\n", i);
	return;
    }

   // gets the node and index in that node where we're going to add the new data
   Location *l = getLocation(i, list);
   Node *toAdd = l->node;
   int index = l->index;

   // number of blocks we've moved over from the block we found above
   int block = 0;

   // walk through the list until we find a node with space, run off the end, or get
   // blockSize blocks in without finding space
   while (block < list->blockSize && toAdd != list->dummy && toAdd->deque->size == list->blockSize+1) {
       toAdd = toAdd->next;
       ++block;
   }

   // if we move over blockSize times, we need to add a new node and spread the data
   // around so that everything is back to size blockSize
   if (block == list->blockSize) {
       spread(l->node, list->blockSize);
       toAdd = l->node;
   }

   // if we're at the dummy, we ran off the end of the list, so add a new node there
   // and move things to make some room
   if (toAdd == list->dummy) {
       // add new node right before toAdd
       toAdd = addBeforeNode(toAdd, list->blockSize);
   }

   // if we're not already at the node we want to add to, move things into the current
   // node and then step back in the list, moving things until we get back to the node
   // we want, which should now have space to add
   while (toAdd != l->node) {
       addToFront(removeFromBack(toAdd->prev->deque), toAdd->deque);
       toAdd = toAdd->prev;
   }

   // now add to the node we wanted at the index we wanted and increment the size
   addToIndex(index, data, toAdd->deque);
   list->size++;
   
   // free the location and it's node now that we have what we need
   free(l);
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

void freeSELList(SELList *list) {
    Node *current = list->dummy->next;
    Node *delete;

    while (current != list->dummy) {
	delete = current;
	current = current->next;
	freeDeque(delete->deque);
	free(delete);
    }

    free(current);
    free(list);
}

