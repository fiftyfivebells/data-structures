package java_structures;

import java.util.Comparator;

class DefaultComparator<T> implements Comparator<T> {
  @SuppressWarnings("unchecked")
  public int compare(T x, T y) {
    return ((Comparable<T>) x).compareTo(y);
  }
}
