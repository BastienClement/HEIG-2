/*
 * Fichier 	: Stack.java
 * Date		: 29.10.2015
 * But 		: Permet l'implémentation d'une pile itérable.
 * Auteur	: Bastien Clément / Alain Hardy
 */

package util;

import java.util.EmptyStackException;
import java.util.Iterator;

/**
 * Une pile.
 */
public class Stack<T> implements Iterable<T> {
    /**
     * Un élément de la liste chainée formant la pile.
     * Note: utilisation de la visibilité publique puisque
     * les objets de cette classe ne sont jamais exposés à
     * l'extérieur de la classe Stack.
     */
    private class Element {
        public T data;
        public Element next;

        Element(T data, Element next) {
            this.data = data;
            this.next = next;
        }
    }

    /**
     * Iterateur sur la pile
     */
    class StackIterator implements Iterator<T> {
        /**
         * L'élément courrant de l'itération
         */
        private Element current;

        StackIterator(Element current) {
            this.current = current;
        }

        /**
         * Est-ce qu'il y a encore un élément auquel accéder ?
         */
        public boolean hasNext() {
            return current != null;
        }

        /**
         * Retourne le prochain élément
         */
        public T next() {
            T data = current.data;
            current = current.next;
            return data;
        }
    }

    /**
     * Taille de la pile
     */
    private int size = 0;

    /**
     * Sommet actuel de la pile
     */
    private Element top = null;

    /**
     * Ajoute un élément au sommet de la pile
     */
    public void push(T data) {
        top = new Element(data, top);
        size++;
    }

    /**
     * Retire et retourne l'élément au sommet de la pile
     */
    public T pop() {
        if (top == null) {
            throw new EmptyStackException();
        }

        T data = top.data;
        top = top.next;
        size--;

        return data;
    }

    /**
     * Retourne une représentation textuelle de la pile.
     */
    public String toString() {
        String s = "[";

        Element l = top;
        while (l != null) {
            s += " <" + l.data.toString() + ">";
            l = l.next;
        }

        s += " ]";
        return s;
    }

    /**
     * Transforme la pile en un tableau d'object.
     * À cause des limitations de la généricité Java,
     * il n'est pas possible de retourner un T[],
     * uniquement un Object[].
     */
    public Object[] toArray() {
        Object[] a = new Object[size];

        Element l = top;
        for (int i = 0; l != null; i++, l = l.next) {
            a[i] = l.data;
        }

        return a;
    }

    /**
     * Retourne un itérateur sur la pile
     */
    public Iterator<T> iterator() {
        return new StackIterator(top);
    }

    /**
     * Retourne la taille de la pile
     */
    public int size() {
        return size;
    }
}

