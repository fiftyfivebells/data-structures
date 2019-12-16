package java_structures;

import java.util.AbstractList;

public class MyArrayDeque<T> extends AbstractList<T> {

  /** Keeps track of the class of objects stored, and allows the creation of generic arrays */
  protected Factory<T> factory;

  /** The backing array that holds all the data */
  protected T[] array;

  /** A pointer to the front element in this list */
  protected int front;

  /** A counter to keep track of the size of the list */
  protected int size;

  /**
   * Constructor
   *
   * @param t is the class of the type of object stored in this list
   */
  public MyArrayDeque(Class<T> t) {
    factory = new Factory(t);
    array = factory.newArray(1);
    size = 0;
    front = 0;
  }

  /** Returns the number of items currently in the array */
  public int size() {
    return size;
  }

  /**
   * Takes an int representing an index and returns the item in the array that is stored at that
   * index.
   *
   * @param i the index of the item in the array
   * @return the item retrieved from the array
   */
  public T get(int i) {
    if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

    return array[(front + i) % array.length];
  }

  /**
   * Takes an int representing and index and an object, then replaces the object at that index with
   * the given object. Returns the object that was replaced.
   *
   * @param i the index of the item in the array
   * @param x the object to replace the one found
   * @return y the object that was replaced
   */
  public T set(int i, T x) {
    if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

    T y = this.get(i);

    array[(front + i) % array.length] = x;

    return y;
  }

  /**
   * Adds an element to the list at the given index. It shifts elements either to the front or the
   * back depending on where the element is being inserted. This method uses modular arithmetic to
   * make the array circular so that it "wraps around" when it hits the end.
   *
   * @param i is the index to insert the new item
   * @param x is the item to insert
   */
  public void add(int i, T x) {
    if (i < 0 || i > size) throw new IndexOutOfBoundsException();

    if (size == array.length) resize();

    if (i < size / 2) {
      front = (front == 0) ? array.length - 1 : front - 1;
      for (int j = 0; j < i; j++)
        array[(front + j) % array.length] = array[(front + j + 1) % array.length];
    } else {
      for (int j = size; j > i; j--)
        array[(front + j) % array.length] = array[(front + j - 1) % array.length];
    }
    array[(front + i) % array.length] = x;
    size++;
  }

  /**
   * Removes an element from the given index. It works like add: it shifts elements either from the
   * front or the back depending on whether the removal is coming from the front or back half of the
   * list. This also uses modular arithmetic to make the array circular.
   *
   * @param i the index to remove from
   * @return x the item being removed from the list
   */
  public T remove(int i) {
    if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();
    T x = array[(front + i) % array.length];

    if (i < size / 2) {
      for (int j = i; j > 0; j--)
        array[(front + j) % array.length] = array[(front + j - 1) % array.length];
    } else {
      for (int j = i; j < size - 1; j++)
        array[(front + j) % array.length] = array[(front + j + 1) % array.length];
    }

    size--;
    if (3 * size < array.length) resize();

    return x;
  }

  /**
   * Creates a new array that is twice the length of the size attribute and copies each element from
   * the current array into the new one, then sets the backing array to the new array. Also resets
   * the array so that the front pointer is pointing back at index 0.
   */
  private void resize() {
    // if size is 0, this will make an array of length 1
    T[] newArray = factory.newArray(Math.max(1, size * 2));

    for (int i = 0; i < size; i++) newArray[i] = array[(front + i) % array.length];

    array = newArray;
    front = 0;
  }

  /** Clears out the array */
  public void clear() {
    size = 0;
    resize();
  }
}
