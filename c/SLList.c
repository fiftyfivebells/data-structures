#include <stdlib.h>
#include "SLList.h"

typedef struct SLNode {
    int data;
    struct SLNode *next;
} SLNode;

typedef struct SLList {
    int size;
    struct SLNode *head;
    struct SLNode *tail;
} SLList;

void add(int i, int data, SLList *list) {
    int      currPos = 0;  // our current position in the list
    SLNode  *current = list->head;  // current node is the head of the list
    SLNode *previous = NULL;

    while(current != NULL) {
	if (currPos == i) break;

	
    }
}

