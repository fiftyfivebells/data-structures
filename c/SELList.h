#include "BoundedDeque.h"

/* Type Definitions */
typedef struct SELLNode {
    BDeque *deque;
    struct SELLNode *prev;
    struct SELLNode *next;
} Node;

typedef struct SELList {
    int size;
    int blockSize;
    Node *dummy;
} SELList;

typedef struct Location {
    Node *node;
    int index;
} Location;

/* Function Definitions */

// Initialize the list
SELList * newSELList(int blockSize);

// Add methods: adds to front, back, or specified index
void SELLaddToIndex(int i, int data, SELList *list);
void addHead(int data, SELList *list);
void addTail(int data, SELList *list);

// Remove methods: removes from front, back, or specified index
int SELLremoveFromIndex(int i, SELList *list);
int removeHead(SELList *list);
int removeTail(SELList *list);

// Get/Set methods
int getIndexSELL(int i, SELList *list);
int setIndexSELL(int i, int data, SELList *list);

// List utility methods
Node * makeNewNode(int blockSize);
void printList(SELList *list);
void printDataList(int** dataList);

