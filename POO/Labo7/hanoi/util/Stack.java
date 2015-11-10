package util;

import java.util.Iterator;
import java.util.NoSuchElementException;

class EmptyStackIterator<T> implements Iterator<T> {
	public boolean hasNext() { return false; }
	public T next() { throw new NoSuchElementException(); }
}

public class Stack<T> implements Iterable<T> {

	private int size;
	private List<T> top;

	public void push(T data) {
		top = new List<T>(data, top);
		size++;
	}
	
	public T pop() {
		if(top == null)
			throw new RuntimeException("The stack is empty.");
		
		T data = top.head;
		top = top.tail;
		size--;
		
		return data;
	}
	
	public String toString() {
		String s = "[";
		
		List<T> l = top;		
		while(l != null) {
			s += " <" + l.head.toString() + ">";
			l = l.tail;
		}
		
		s += " ]";
		return s;
	}
	
	public Object[] toArray() {
		Object[] a = new Object[size];
		
		List<T> l = top;
		for(int i = 0; l != null; i++, l = l.tail) {
			a[i] = l.head;
		}
		
		return a;
	}

	public Iterator<T> iterator() {
		return (top == null) ? new EmptyStackIterator<T>() : top.iterator();
	}

	public int size() {
		return size;
	}
	
}

