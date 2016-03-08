/**
 * Labo 01 - Observer Pattern
 * Clock.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package gui;

import timer.StopWatch;
import utils.ClickListener;
import utils.Observer;

import javax.swing.*;
import java.awt.*;

/**
 * Classe abstraite d'horloge.
 * Une horloge observer un objet StopWatch qui lui fourni le
 * temps écoulé et met à jour son affichage en conséquence.
 */
public abstract class Clock extends JPanel implements Observer {
	/** L'objet StopWatch observé par l'horloge */
	protected StopWatch stopWatch;

	/**
	 * Constructeur
	 * @param sw L'objet StopWatch à observer
	 */
	public Clock(StopWatch sw) {
		stopWatch = sw;
		stopWatch.addObserver(this);
		addMouseListener((ClickListener)(e) -> stopWatch.toggle());
	}

	/**
	 * Mise à jour de la représentation visuelle de l'horloge
	 * @param g
	 */
	protected void paintComponent(Graphics g) {
		update();
		super.paintComponent(g);
	}

	abstract public void update();

	/**
	 * Retire cette horloge des observateurs de l'objet StopWatch
	 */
	public void dispose() {
		stopWatch.removeObserver(this);
	}
}
