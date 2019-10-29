#include <stdio.h>
#include <stdlib.h>
#include "BoundedDeque.h"

BDeque * newBoundedDeque(int maxSize) {
    BDeque *d = malloc(sizeof(BDeque));

    d->maxSize = maxSize;
    d->size = 0;
    d->front = 0;

    d->dataList = malloc(sizeof(int) * maxSize);

    return d;
}

/**
 * Takes in an index, data to add, and the deque to add the data to. Then,
 * depending on whether it's adding to the first or second half, it shifts
 * elements left or right to make room. If there's no room, it prints a
 * message and returns.
 */ 
void addToIndex(int i, int data, BDeque *d) {
    if (i > d->size+1) {
	printf("Index %d is out of bounds.\n", i);
	return;
    }

    // if adding to the end, just put it there
    if (i == d->size)
	d->dataList[(d->front + d->size)%d->maxSize] = data;

    else {

	// if in the first half of the list, shift things left
	if (i <= d->size / 2) {
	    // reset the front pointer to one to the left, which could mean wrapping it around
	    // to the end of the list if we're already at the front
	    d->front = (d->front == 0) ? d->maxSize - 1 : d->front - 1;

	    // the actual index in the list
	    int index = (d->front + i) % d->maxSize;

	    for (int j = 0; j < i; i++) {
		// starts at the new front, moves everything over one until it gets to the new index
		d->dataList[(d->front+i)%d->maxSize] = d->dataList[(d->front+i+1)%d->maxSize];
	    }

	    d->dataList[index] = data;
	}

	// otherwise, shift things right
	else {
	    for (int j = d->size; j > i; i--) {
		// starts at the new end, moves everything to the right until it gets to the index
		d->dataList[(d->front+i)%d->maxSize] = d->dataList[(d->front+i-1)%d->maxSize];
	    }
	}	
    }

    d->size++;
}

/**
 * Adds to the very front of the list
 */ 
void addToFront(int data, BDeque *d) {
    addToIndex(0, data, d);
}

/**
 * Adds to the back of the list
 */
void addToBack(int data, BDeque *d) {
    addToIndex(d->size, data, d);
}

