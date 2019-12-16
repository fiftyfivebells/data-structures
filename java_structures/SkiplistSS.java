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

    public int height() {
      return next.length - 1;
    }
  }

  /** The node that sits to the left of the skiplist and holds all the search paths */
  protected Node<T> sentinel;

  /** Used by the add(x) method to store the nodes traversed */
  protected Node<T>[] stack;

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
  @SuppressWarnings("unchecked")
  public SkiplistSS(Comparator<T> c) {
    // set max height of sentinel to 32 (no node is likely to get that tall)
    sentinel = new Node<T>(null, 32);

    stack = (Node<T>[]) Array.newInstance(Node.class, sentinel.next.length);
    comp = c;
    prng = new Random();
    height = 0;
    size = 0;
  }

  /** Constructor: No argument constructor uses the default comparator. */
  public SkiplistSS() {
    this(new DefaultComparator<T>());
  }

  /**
   * Adds the provided element into the sorted set at the point where it should go.
   *
   * @param x The element to add into the set.
   * @return true if the element was added, false otherwise
   */
  public boolean add(T x) {
    Node<T> u = sentinel;
    int h = height;
    int c = 0;

    while (h >= 0) {
      while (u.next[h] != null && (c = comp.compare(u.next[h].x, x)) < 0) u = u.next[h];

      if (u.next[h] != null && c == 0) return false;
      stack[h--] = u; // stores the node in the stack as we descend the path
    }

    Node<T> w = new Node<T>(x, chooseHeight());

    // as long as the new node's height is greater than the height of the highest node in the set,
    // add references back to the sentinel until height matches the new node's height
    while (height < w.height()) stack[++height] = sentinel;

    // for each reference in the new node, set its next to the corresponding node in the stack
    // array, and set the stack array's corresponding node's next to the new node
    for (int i = 0; i < w.next.length; i++) {
      w.next[i] = stack[i].next[i];
      stack[i].next[i] = w;
    }

    // increment size and return true, since we got through to the end and successfully added
    size++;
    return true;
  }

  /**
   * Chooses a random height for the new node by increasing the its count by 1 each time it
   * encounters a 1 in the least significant bit of a randomly generator number. Compares it with 1
   * for the first round, then continues shifting the bits of the 1 to the left each time. Returns
   * the number of 1s it encountered.
   *
   * @return the new height of the node
   */
  private int chooseHeight() {
    int count = 0;
    int z = prng.nextInt();
    int x = 1;

    while ((z & x) != 0) {
      count++;
      x <<= 1;
    }

    return count;
  }
  /**
   * Takes in an item x and searches through the skiplist for the node right before the node
   * containing the data we're after, or right before where that node would be. Then returns that
   * prior node
   *
   * @param x The item being searched for
   * @return the node just before the node we want (or before where it would be)
   */
  private Node<T> findPrevNode(T x) {
    Node<T> u = sentinel;
    int h = height;
    while (h >= 0) {
      while (u.next[h] != null && comp.compare(u.next[h].x, x) < 0) u = u.next[h];
      h--;
    }
    return u;
  }

  /**
   * Uses the findPrevNode method to get the node before what we're looking for, then either returns
   * the following node if its data property is what we want or null otherwise.
   *
   * @param x The item we're searching for
   * @return the node we want, or null if it doesn't exist
   */
  private T find(T x) {
    Node<T> u = findPrevNode(x);
    return (u.next[0] == null) ? null : u.next[0].x;
  }
}
