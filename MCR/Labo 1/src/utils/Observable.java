package utils;

import java.util.LinkedList;

public abstract class Observable {
	private LinkedList<Observer> observers = new LinkedList<>();

	public void addObserver(Observer observer) {
		removeObserver(observer);
		observers.add(observer);
	}

	public void removeObserver(Observer observer) {
		observers.remove(observer);
	}

	protected void notifyObservers() {
		observers.forEach(Observer::update);
	}
}
