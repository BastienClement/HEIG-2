/**
 * Labo 01 - Observer Pattern
 * DigitalClock.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package gui;

import timer.StopWatch;

import javax.swing.*;

/**
 * Une horloge digitale, avec affichage des dixièmes de secondes.
 */
public class DigitalClock extends Clock {
	/** Le label utilisé pour afficher le temps */
	private final JLabel label = new JLabel("00:00:00.0");

	/**
	 * Constructeur
	 * @param sw L'objet StopWatch à observer
	 */
	public DigitalClock(StopWatch sw) {
		super(sw);
		add(label);
	}

	/**
	 * La StopWatch nous a notifié d'un changement.
	 * Mise à jour de l'affichage de l'heure.
	 */
	public void update() {
		long time = stopWatch.getTime();

		long millis  = time % 1000;
		long seconds = (time /= 1000) % 60;
		long minutes = (time /= 60) % 60;
		long hours   = (time / 60) % 24;

		label.setText(String.format("%02d:%02d:%02d.%01d", hours, minutes, seconds, millis / 100));
	}
}
