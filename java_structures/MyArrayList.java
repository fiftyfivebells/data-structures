package java_structures;

import java.util.AbstractList;
import java.util.Collection;

/**
 * This is my implementation of Java's ArrayList class. I've implemented
 * this with an array, with elements stored at array[0],...,array[size - 1].
 * The array doubles in size when it hits capacity, and it halves in size
 * when it hits a third of capacity.
 */
public class MyArrayList<T> extends AbstractList<T> {
    
    /**
     * Keeps track of the class of objects stored, and
     * allows creation of generic arrays
     */
    protected Factory<T> factory;

    /**
     * The array that stores the elements
     */
    protected T[] array;

    /**
     * The number of elements stored in the array
     */
    protected int size;

    /**
     * Constructor
     * @param t is the class of the type of object stored in the list
     */
    public MyArrayList(Class<T> t) {
        factory = new Factory(t);
        array = factory.newArray(1);  // makes new array of size 1
        size = 0;
    }

    /**
     * Returns the number of items currently in the array
     */
    public int size() {
        return size;
    }

    /**
     * Takes an integer representing an index in the list and
     * returns the item at that index. Does not remove the item
     * from the list.
     * @param i The index of the item from the list
     * @return x The value at the given index
     */
    public T get(int i) {
        if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

        return array[i];
    }

    /**
     * Takes an integer representing an index in the list and an element
     * and then sets the item at that index to the new element. Returns
     * the original item.
     * @param i the index to put the new item
     * @param x the object to be added
     * @return the item in the index before being set
     */
    public T set(int i, T x) {
        if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

        T y = array[i];
        array[i] = x;
        return y;
    }

    /**
     * Takes an object of type T and adds it to the array at index i.
     * If the array is at capacity, it resizes, then adds.
     * @param i the index to put the new item
     * @param x the object to be added
     */
    public void add(int i, T x) {
        if (i < 0 || i > size) throw new IndexOutOfBoundsException();

        if (size == array.length) resize();

        for (int j = size; j > i; j--) {
            array[j] = array[j-1];
        }
        array[i] = x;
        size++;
    }
    
    /**
     * Removes and returns the object at index i in the array. If the
     * array is equal or greater than 3 times size after the remove, it
     * resizes the backing array.
     * @param i index to remove from
     * @return x the item removed from the array
     */
    public T remove(int i) {
        if (i < 0 || i > size - 1) throw new IndexOutOfBoundsException();

        T x = array[i];

        for (int j = i; j < size - 1; j++) {
            array[j] = array[j+1];
        }

        size--;
        if (size*3 <= array.length) resize();

        return x;
    }

    /**
     * Resizes the internal array when the number of items being stored
     * is either equal to the length of the array, or when the number
     * of items stored is 1/3 the length of the array.
     */
    private void resize() {
        // take max of 1 and size*2 to account for when size is 0
        T[] newArray = factory.newArray(Math.max(size*2, 1));
        for (int i = 0; i < size*2; i++) {
            newArray[i] = array[i];
        }
        array = newArray;
    }
}
