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

/**
 * Add functions
 */
void addHead(int data, SELList *list) {

    // if there are no nodes in the list, add one
    if (list->dummy->next == NULL) {
	list->dummy->next = malloc(sizeof(Node));
	list->dummy->next->dataList = malloc(sizeof(int) * list->blockSize);
    }

    Node *head = list->dummy->next;

    head->dataList[0] = &data;

}

/**
 * List Utility Methods:
 * printList
 */
void printList(SELList *list) {
    Node *head = list->dummy;

    printf("[");
    while (head->next != NULL) {
	printDeque(head->next->deque);
	head = head->next;
    }
    printf("\n");
}

