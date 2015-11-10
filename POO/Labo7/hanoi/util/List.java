package util;

import java.util.Iterator;
import java.util.NoSuchElementException;

class ListIterator<T> implements Iterator<T> {
	List<T> current;

	public ListIterator(List<T> l) {
		current = l;		
	}
	
	public boolean hasNext() {
		return current != null;
	}

	public T next() {
		if(!hasNext())
			throw new NoSuchElementException();
		
		T t = current.head;		
		current = current.tail;
		
		return t;
	}	
}

public class List<T> implements Iterable<T> {
	public final T head;
	public final List<T> tail;

	List(T d, List<T> t) {
		head = d;
		tail = t;
	}

	public Iterator<T> iterator() {
		return new ListIterator<T>(this);
	}
}
