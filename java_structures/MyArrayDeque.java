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
        
    }
}
