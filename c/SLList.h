/* Type Definitions */
typedef struct SLNode {
    int data;
    struct SLNode *next;
} SLNode;

typedef struct SLList {
    int size;
    struct SLNode *head;
    struct SLNode *tail;
} SLList;

/* Function Definitions */

// adds given int at given index in the provided list, or to the back/fronvoid add(int i, int data, SLList *list);
void addNode(int data, SLList *list);
void addHead(int data, SLList *list);
void addTail(int data, SLList *list);

// removes from the given index in the provided list, frees the node, and returns the value
int removeNode(int i, SLList *list);
int removeHead(SLList *list);
int removeTail(SLList *list);

// get/set value at given index in the provided list
int get(int i, SLList *list);
void set(int i, int data, SLList *list);

// creates a new node and returns a pointer to it
SLNode* makeNode(int data);

// prints out a text representation of the linked list
void printList(SLList *list);

