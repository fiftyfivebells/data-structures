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

void addToIndex(int i, int data, BDeque *d) {
    if (i > d->size+1) {
	printf("Index %d is out of bounds.\n", i);
	return;
    }

    if (i == d->size)
	d->dataList[(d->front + d->size)%d->maxSize] = data;

    else {


	if (i <= d->size / 2) {
	    d->front = (d->front == 0) ? d->maxSize - 1 : d->front - 1;
	    int index = (d->front + i) % d->maxSize;

	    for (int j = 0; j < i; i++) {
		printf("It shouldn't be entering here\n");
		d->dataList[(d->front+i)%d->maxSize] = d->dataList[(d->front+i+1)%d->maxSize];
	    }

	    d->dataList[index] = data;
	} else {
	    for (int j = d->size; j > i; i--) {
		d->dataList[(d->front+i)%d->maxSize] = d->dataList[(d->front+i-1)%d->maxSize];
	    }
	}	
    }

    d->size++;
}

