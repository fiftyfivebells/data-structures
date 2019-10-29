/* Type Definitions */
typedef struct BoundedDeque {
    int maxSize;    // the most elements the list can hold
    int size;       // number of elements in list
    int *dataList;  // list of elements
    int front;      // index of front item in list
} BDeque;

/* Function Definitions */

// Initialize the deque
BDeque * newBoundedDeque(int maxSize);

// Add Functions
void addToIndex(int i, int data, BDeque *d);
void addToFront(int data, BDeque *d);
void addToBack(int data, BDeque *d);

// Remove Functions
int removeFromIndex(int i, BDeque *d);
int removeFromFront(BDeque *d);
int removeFromBack(BDeque *d);

// Get/Set Functions
int getIndex(int i, BDeque *d);
void setIndex(int i, int data, BDeque *d);

// Utility Methods
void printDeque(BDeque *d);
void freeDeque(BDeque *d);

