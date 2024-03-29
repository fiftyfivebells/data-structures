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

	    for (int j = 0; j < i; j++) {

		// starts at the new front, moves everything over one until it gets to the new index
		d->dataList[(d->front+j)%d->maxSize] = d->dataList[(d->front+j+1)%d->maxSize];
	    }

	    d->dataList[index] = data;
	}

	// otherwise, shift things right
	else {
	    for (int j = d->size; j > i; j--) {

		// starts at the new end, moves everything to the right until it gets to the index
		d->dataList[(d->front+i)%d->maxSize] = d->dataList[(d->front+j-1)%d->maxSize];
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

/**
 * Takes the item from the head of the list and updates the list
 */
int removeFromFront(BDeque *d) {
    if (d->size == 0) {
	printf("Nothing to remove from this list.\n");
	return -1;
    }

    // get the item we're removing from the list
    int x = d->dataList[d->front];

    // update the front pointer to the next in line
    d->front = (d->front+1) % d->maxSize;
    d->size--;
    return x;
}

/**
 * Takes the item from the back of the list and updates the list
 */
int removeFromBack(BDeque *d) {
    if (d->size == 0) {
	printf("Nothing to remove from this list.\n");
	return -1;
    }


    int x = d->dataList[((d->front)+(d->size-1))%d->maxSize];
    d->size--;
    return x;
}

int removeFromIndex(int i, BDeque *d) {
    if (i < 0 || i > d->size-1) {
	printf("REMOVE: Index %d is out of bounds.\n", i);
	exit(-1);
    }

    if (d->size == 0) {
	printf("Nothing to remove from this list.\n");
	exit(-1);
    }

    if (i == 0)
	return removeFromFront(d);

    if (i == d->size-1)
	return removeFromBack(d);

    int x = d->dataList[(d->front + i) % d->maxSize];

    // if in the first half of the list, start at the index we removed from and
    // pull each item from before it one by one, until we've hit the front
    if (i <= d->size / 2) {
	for (int j = i; j > 0; j--) {
	    d->dataList[(d->front+j)%d->maxSize] = d->dataList[(d->front+j-1)%d->maxSize];
	}
	d->front = (d->front+1) % d->maxSize;
    }

    // if in the back half of the list, start at the index and move each thing
    // after it over by one until we hit the back of the list
    else {
	for (int j = i; j < d->size-1; j++) {
	    d->dataList[(d->front+j)%d->maxSize] = d->dataList[(d->front+j+1)%d->maxSize];
	}
    }

    d->size--;
    return x;
}

int getIndex(int i, BDeque *d) {
    if (i < 0 || i > d->size-1) {
	printf("Index %d is out of bounds.\n", i);
	exit(-1);
    }

    if (d->size == 0) {
	printf("Nothing to get from this list.\n");
	exit(-1);
    }

    return d->dataList[(d->front+i)%d->maxSize];
}

void setIndex(int i, int data, BDeque *d) {
    if (i < 0 || i > d->size-1) {
	printf("Index %d is out of bounds.\n", i);
	return;
    }

    if (d->size == 0) {
	printf("Nothing to get from this list.\n");
	return;
    }

    d->dataList[(d->front+i)%d->maxSize] = data;
}

void printDeque(BDeque *d) {
    printf("[");

    for (int i = 0; i < d->size; i++) {
	if (i == d->size - 1)
	    printf("%d", d->dataList[(d->front+i)%d->maxSize]);
	else
	    printf("%d, ", d->dataList[(d->front+i)%d->maxSize]);
    }
    printf("]");
}

void freeDeque(BDeque *d) {
    free(d->dataList);
    free(d);
}

