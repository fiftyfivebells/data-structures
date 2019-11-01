# Data Structures

These are various implementations of abstract data types using different data structures in different languages. The intent here is to deepen my understanding of the data structures I've learned about in my abstract data types and algorithms class, and also to get a feel for implementing them in different languages.

## Linked Lists
I've made a couple different implementations of the List interface with Linked Lists. In C, I implemented the Singly Linked List, and a structure called the Space-Efficient Linked List

### Singly-Linked List
This is just a straightforward Linked List, where each node has a piece of data and a pointer to the next node. Once you go to a node, there's no way to go backwards in the list. This implementation has a reference to the head and tail of the list, so there is O(1) access to the first and last elements of the list. This means that adding to the front or back, or getting/setting at the front or back, is a constant time operation.

However, since this is a Linked List, add/remove and get/set are O(1+i) operations when accessing anything that's not at the head or tail. In the worse case, this is O(n).

### Space-Efficient Linked List
A different take on the linked list, this is really just a special case of the Doubly-Linked List. Each node has a pointer to the next node in the list as well as the previous node in the list. However, storing a single item in each node of the Doubly-Linked List is a bit of a waste of space, as depending on the size of each piece of data, the pointers could take up more space than what you're storing. To take care of that issue, each node holds a block of data instead of just a single piece.

I implemented this with a dummy node in the beginning, where the head and tail are the dummy's next and previous nodes respectively. This makes it into a circular list. There's still constant time get/set and add/remove for the items at the front and back of the list, like the Singly-Linked List, but there's a bit of an improvement on access since we can enter from either the front or the back. In a Singly-Linked List, the worst case scenario for adding/removing is the node right before the tail. In the Space-Efficient Linked List (and Doubly-Linked List), the worst case is the middle element. This is still in the same complexity class, but it's an improvement to O(n/2).

## Arrays
These are List implementations that use an array as the backing structure. In C, I may also use a pointer to a list of values instead of an array.

### Bounded Deque
This structure is the internal structure for the blocks in the Space-Efficient Linked List. It implements the list in a circular way so that adding/removing from the front and back are faster than a standard array. I keep a reference to the front, which is an index in the list, the number of items in the list, and the maximum size of the list. When adding to the front, it just decremenets the front index and adds the new element there. If it's already at 0, the array "wraps around" and sets the front to the last index in the list. It does the same with adding at the end of the list.

This is useful as a block for the SE Linked List because it gives O(1) add and remove from the front and the back. Since the SE Linked List does a lot of shifting elements from the front of one block to the back of another, or vice versa, this facilitates those operations in an efficient way.
