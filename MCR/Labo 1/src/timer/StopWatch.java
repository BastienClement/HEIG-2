/**
 * Labo 01 - Observer Pattern
 * StopWatch.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package timer;

import utils.Observable;

import java.util.Timer;
import java.util.TimerTask;

/**
 * Chronomètre
 */
public class StopWatch extends Observable {
	/** Intervalle de tick du timer */
	private static int interval = 15;

	/** Timer utilisé pour compter le temps */
	private Timer timer;

	/** Temps actuel en millisecondes */
	private long time = 0;

	/**
	 * Lance le chronomètre
	 */
	public void start() {
		if (timer != null) return;
		timer = new Timer(true);
		timer.scheduleAtFixedRate(ticker(), interval, interval);
	}

	/**
	 * Fabrique l'objet responsable de recevoir les ticks du timer
	 */
	private TimerTask ticker() {
		return new TimerTask() {
			public void run() {
				tick();
			}
		};
	}

	/**
	 * Un tick du timer
	 */
	private void tick() {
		time += interval;
		notifyObservers();
	}

	/**
	 * Arrête le chronomètre
	 */
	public void stop() {
		if (timer == null) return;
		timer.cancel();
		timer = null;
	}

	/**
	 * Retourne le temps écoulé depuis le départ du chronomètre
	 */
	public long getTime() {
		return time;
	}

	/**
	 * Réinitialise le chronomètre à zero
	 */
	public void reset() {
		time = 0;
		notifyObservers();
	}

	/**
	 * Alterne l'état d'activation du chronomètre
	 */
	public void toggle() {
		if (timer == null) start();
		else stop();
	}
}
