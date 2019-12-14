package java_structures;

import java.util.AbstractList;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Test {
    public static void main(String[] args) {
        List<Integer> ml = new MyArrayList<Integer>(Integer.class);
        List<Integer> al = new ArrayList<Integer>();
        Random prng = new Random();

        for (int i = 0; i < 1000; i++) {
            ml.add(i, i);
            al.add(i, i);
        }

        System.out.print("These two lists are equal: ");
        System.out.println(ml.equals(al));

        ml.clear();
        al.clear();

        for (int i = 0; i < 1000; i++) {
            ml.add(0, i);
            al.add(0, i);
        }

        System.out.print("These two lists are equal: ");
        System.out.println(ml.equals(al));


        ml.clear();
        al.clear();

        for (int i = 0; i < 10; i++) {
            int index = prng.nextInt(i+1);
            ml.add(index, i);
            al.add(index, i);
        }

        System.out.print("These two lists are equal: ");
        System.out.println(ml.equals(al));
    }
}
