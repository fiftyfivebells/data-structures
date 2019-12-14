package java_structures;

import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;

public class Test {
    public static void main(String[] args) {
        List<Integer> ml = new MyArrayList<Integer>(Integer.class);
        List<Integer> al = new ArrayList<Integer>();

        for (int i = 0; i < 1000; i++) {
            ml.add(i);
            al.add(i);
        }

        System.out.print("These two lists are equal: ");
        System.out.println(ml.equals(al));

        ml.clear();
        al.clear();

        for (int i = 0; i < 1000; i++) {
            ml.add(0);
            al.add(0);
        }

        System.out.print("These two lists are equal: ");
        System.out.println(ml.equals(al));


    }
}
