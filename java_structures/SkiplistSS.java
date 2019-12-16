package java_structures;

import java.lang.reflect.Array;
import java.util.Random;

public class SkiplistSS<T> {

  /**
   * The nodes that make up the skiplist. It holds a piece of data as well as an array of pointers
   * to the next node in its list. It also has a height, which is the height of its next list.
   */
  protected static class Node<T> {
    T x;
    Node<T>[] next;

    @SuppressWarnings("unchecked")
    public Node(T x, int h) {
      this.x = x;
      next = (Node<T>[]) Array.newInstance(Node.class, h + 1);
    }
  }

  /** The node that sits to the left of the skiplist and holds all the search paths */
  protected Node<T> sentinel;

  /** The height of the highest element in the skiplist */
  int height;

  /** The total size of skiplist (how many elemnts it holds) */
  int size;

  /** The pseudo-random number generator (to get the heights) */
  Random prng;
}
