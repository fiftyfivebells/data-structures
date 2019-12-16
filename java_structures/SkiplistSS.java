package java_structures;

import java.lang.reflect.Array;
import java.util.Comparator;
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
  protected int height;

  /** The total size of skiplist (how many elemnts it holds) */
  protected int size;

  /** The pseudo-random number generator (to get the heights) */
  protected Random prng;

  /** The comparator to allow the node values to be compared */
  protected Comparator<T> comp;

  /**
   * Constructor: Creates the sentinel node and random number generator, and also sets the height
   * and size to 0
   */
  public SkiplistSS(Comparator<T> c) {
    // set max height of sentinel to 32 (no node is likely to get that tall)
    sentinel = new Node<T>(null, 32);
    comp = c;
    prng = new Random();
    height = 0;
    size = 0;
  }
}
