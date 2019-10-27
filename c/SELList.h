/* Type Definitions */
typedef struct SELLNode {
    int **data;  // pointer to a list of int values
    struct SELLNode *prev;
    struct SELLNode *next;
} Node;

typedef struct SELList {
    int size;
    Node *dummy;
} SELList;

/* Function Definitions */

// Initialize the list
SELList * newSELList(int blockSize);

// Add methods: adds to front, back, or specified index
void addToIndex(int i, int data, SELList *list);
void addHead(int data, SELList *list);
void addTail(int data, SELList *list);

// Remove methods: removes from front, back, or specified index
int removeFromIndex(int i, SELList *list);
int removeHead(SELList *list);
int removeTail(SELList *list);

// Get/Set methods
int getIndex(int i, SELList *list);
int setIndex(int i, int data, SELList *list);
