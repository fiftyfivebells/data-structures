/* Type Definitions */
typedef struct SLNode SLNode;
typedef struct SLList SLList;

/* Function Definitions */

// adds given int at given index in the provided list, or to the back/fronvoid add(int i, int data, SLList *list);
void addHead(int data, SLList *list);
void addTail(int data, SLList *list);

// removes from the given index in the provided list
int remove(int i, SLList *list);

// get/set value at given index in the provided list
int get(int i, SLList *list);
void set(int i, int data, SLList *list);

