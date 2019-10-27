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
    list->dummy->prev = NULL;
    list->dummy->next = NULL;

    return list;
}

