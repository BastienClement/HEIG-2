/**
 * Labo 01 - Observer Pattern
 * Observable.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package utils;

import java.util.LinkedList;

/**
 * Un sujet observable
 */
public abstract class Observable {
	/** Liste des observateurs enregistrés pour ce sujet */
	private LinkedList<Observer> observers = new LinkedList<>();

	/**
	 * Ajoute un nouvel observateur à ce sujet
	 * @param observer  L'observateur
	 */
	public void addObserver(Observer observer) {
		removeObserver(observer);
		observers.add(observer);
	}

	/**
	 * Supprime un observateur
	 * @param observer  L'observateur
	 */
	public void removeObserver(Observer observer) {
		observers.remove(observer);
	}

	/**
	 * Notifie les observateurs d'un changement d'état du sujet
	 */
	protected void notifyObservers() {
		observers.forEach(Observer::update);
	}
}
