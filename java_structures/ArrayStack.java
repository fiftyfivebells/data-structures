package java_structures;

import java.util.Stack;

public class ArrayStack extends MyArrayStack<T> implements Stack<T> {

    /**
     * Constructor
     * Calls the parent constructor with the desired class
     * @param t The class type of the object being held by this stack
     */
    public ArrayStack(Class<T> t) {
        super(t);
    }

    /**
     * Pushes the provided object onto the front of the stack
     * @param x the object to be added to the stack
     */
    public void push(T x) {
        this.add(0, x);
    }

    /**
     * Pops the first element off the stack and returns it
     * @return x the top element of the stack
     */
    public T pop() {
        return this.remove(0);
    }
}
