package java_structures;

import java.util.AbstractList;

public class MyArrayDeque<T> extends AbstractList<T> {

    /**
     * Keeps track of the class of objects stored, and allows the
     * creation of generic arrays
     */
    protected Factory<T> factory;

    /**
     * The backing array that holds all the data
     */
    protected T[] array;

    /**
     * A pointer to the front element in this list
     */
    protected int front;

    /**
     * A counter to keep track of the size of the list
     */
    protected int size;

    /**
     * Constructor
     * @param t is the class of the type of object stored in this list
     */
    public MyArrayDeque(Class<T> t) {
        factory = new Factory(t);
        array = factory.newArray(1);
        size = 0;
        front = 0;
    }

    /**
     * Returns the number of items currently in the array
     */
    public int size() {
        return size;
    }

    /**
     * Takes an int representing an index and returns the item in the array
     * that is stored at that index.
     * @param i the index of the item in the array
     * @return the item retrieved from the array
     */
    public T get(int i) {
        if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

        return array[(front+i)%array.length];
    }

}
