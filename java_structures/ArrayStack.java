package java_structures;

import java.util.Stack;

public class ArrayStack<T> extends MyArrayList<T> {

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

    /**
     * Looks at the top element of the stack without removing it
     * @return the top element of the stack
     */
    public T peek() {
        return this.get(0);
    }

    /**
     * Checks if the stack is empty
     * @return boolean: true if empty, false otherwise
     */
    public boolean empty() {
        return this.size == 0;
    }
}
