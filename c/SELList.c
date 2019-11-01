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

/**
 * Adds the given data to the given list at the given index. If there's no space in
 * the node and index we're looking for, it walks through the list looking for space.
 * If it takes blockSize steps into the list and finds no space, it needs to add a
 * new node, then spread the max capacity nodes out so that it fills the new node to
 * just blockSize, which leaves all the other nodes at blockSize as well. It then
 * adds to the list.
 */
void SELLaddToIndex(int i, int data, SELList *list) {
 
   if (i < 0 || i > list->size) {
	printf("Index %d is out of bounds.\n", i);
	exit(-1);
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
 * Takes an index and the SELList, then removes the data from the given index.
 * Returns the data that was removed, and also closes up the gap left by the
 * remove. If a block drops below blockSize-1, it gathers up excess items from
 * other blocks and removes the now-empty node.
 */
int SELLremoveFromIndex(int i, SELList *list) {
    if (i < 0 || i > list->size-1) {
	printf("Index %d is out of bounds.\n", i);
	exit(-1);
    }

    Location *l = getLocation(i, list);

    // get the item we'll eventually return from the function
    int x = getIndex(l->index, l->node->deque);

    // set current to the node where we found the data to remove
    Node *current = l->node;
    int block = 0;

    // walk through the list until we hit the dummy, find a node 
    // with more than blockSize-1 items, or we've seen blockSize nodes
    while (block < list->blockSize && current != list->dummy && current->deque->size == list->blockSize-1) {
	current = current->next;
	block++;
    }

    // if we've gone blockSize steps into the list, we've got too much space
    // and need to gather some elements to get rid of a node
    if (block == list->blockSize) {
	gather(l->node, list->blockSize);
    }

    // set the current node back to the node we want to remove from
    current = l->node;

    // now actually remove the item from the list
    removeFromIndex(l->index, current->deque);

    // then, while the current node's block size is less than blockSize-1,
    // we pull from the next node, balancing as we go
    while (current->deque->size < list->blockSize-1 && current->next != list->dummy) {
	addToBack(removeFromFront(current->next->deque), current->deque);
	current = current->next;
    }

    // if there's nothing left in the current block, remove the node
    if (current->deque->size == 0) {
	current->prev->next = current->next;
	current->next->prev = current->prev;

	// don't forget to free the deque and the node when we remove
	freeDeque(current->deque);
	free(current);
    }
    
    // free up the location now that we're done
    free(l);

    list->size--;
    return x;
}

/**
 * Standard get function. Takes in the index and the list, then gets
 * and returns the item at that index inside the list.
 */ 
int getIndexSELL(int i, SELList *list) {
    Location *l = getLocation(i, list);
    int x = getIndex(l->index, l->node->deque); 

    // remember to free the allocated memory for the location
    free(l);

    return x;
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

void gather(Node *node, int blockSize) {
    Node *current = node;

    for (int i = 0; i < blockSize-1; i++) {
	while (current->deque->size < blockSize)
	    addToBack(removeFromFront(current->next->deque), current->deque);
	current = current->next;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
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
	while(i >= current->deque->size) {
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
	    current = current->prev;
	    index -= current->deque->size;
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

