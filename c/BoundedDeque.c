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

