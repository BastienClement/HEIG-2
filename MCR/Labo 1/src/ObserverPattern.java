import java.util.TreeSet;

class Data {

}

interface Observer {
	void update();
}

abstract class Observable {
	private TreeSet<Observer> observers = new TreeSet<>();

	public void addObserver(Observer observer) { observers.add(observer); }
	public void removeObserver(Observer observer) { observers.remove(observer); }
	protected void notifyObservers() { observers.forEach(Observer::update); }
}

class ConcreteObservable extends Observable {
	private Data observableState = new Data();

	public Data getState() { return observableState; }
	public void setState(Data state) {
		observableState = state;
		notifyObservers();
	}
}

class ConcreteObserver implements Observer {
	private ConcreteObservable subject = new ConcreteObservable();
	private Data observerState = subject.getState();

	public ConcreteObserver() { update(); }
	public void update() { observerState = subject.getState(); }
}

public class ObserverPattern {
	public static void main(String[] args) {

	}
}
