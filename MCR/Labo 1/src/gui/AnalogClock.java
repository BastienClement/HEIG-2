/**
 * Labo 01 - Observer Pattern
 * AnalogClock.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package gui;

import timer.StopWatch;

import java.awt.*;

/**
 * Une horloge analogique, avec look personnalisable.
 */
public class AnalogClock extends Clock {
	/** Taille par défaut de l'horloge si non-élastique */
	public static final int DEFAULT_CLOCK_SIZE = 300;

	/** Le look de l'horloge choisi par l'utilisateur */
	ClockFace face;

	/** La taille actuelle de l'horloge */
	private int size;

	/** L'image de fond de l'horloge, récupérée depuis la ClockFace */
	private Image img;

	/**
	 * Constructeur
	 * @param face      Le look de l'horloge souhaité
	 * @param sw        Un objet StopWatch à observer
	 * @param elastic   Est-ce que l'horloge est redimmensionnable ?
	 */
	public AnalogClock(ClockFace face, StopWatch sw, boolean elastic) {
		super(sw);
		this.face = face;
		if (!elastic) {
			// Si l'horloge n'est pas redimmensionnable, on lui
			// défini une taille par défaut.
			setPreferredSize(new Dimension(DEFAULT_CLOCK_SIZE, DEFAULT_CLOCK_SIZE));
		}
	}

	/**
	 * Mise à jour du visuel de l'horloge
	 * @param g
	 */
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		int cur_size = Math.min(getHeight(), getWidth());

		if (img == null || size != cur_size) {
			img = face.scaled(cur_size, cur_size);
			size = cur_size;
		}

		// Fond
		g.drawImage(img, 0, 0, null);

		// Déplacement du référentiel au centre de la fenêtre
		g.translate(size / 2, size / 2);

		// Calcul du temps en secondes / minutes / heures
		double seconds = ((double) stopWatch.getTime()) / 1000;
		double minutes = seconds / 60;
		double hours   = minutes / 60;

		// On sait que l'on a reçu un objet Graphic2D
		Graphics2D g2 = (Graphics2D) g;

		// Aiguilles
		drawLine(g2, hours,   12, 6, size / 5, 0x000000);
		drawLine(g2, minutes, 60, 4, size / 3, 0x000000);
		drawLine(g2, seconds, 60, 2, size / 3, 0xFF0000);
	}

	/**
	 * Dessine une des aiguilles de l'horloge.
	 * @param g2        Le contexte graphique du composant Swing
	 * @param val       Le nombre de sec / min / h écoulées
	 * @param max       Le nombre de sec / min / h d'un tour complet
	 * @param width     Largeur de l'aiguille
	 * @param length    Longueur de l'aiguille
	 * @param color     Couleur de l'aiguille
	 */
	private void drawLine(Graphics2D g2, double val, double max, int width, int length, int color) {
		g2.setStroke(new BasicStroke(width));
		g2.setColor(new Color(color));
		double alpha = (val / max) * (Math.PI * 2);
		g2.drawLine(0, 0, (int) (Math.sin(alpha) * length), (int) (-Math.cos(alpha) * length));
	}

	/**
	 * Mise à jour de la représentation visuelle du composant lorsque
	 * l'objet StopWatch nous notifie d'un changement.
	 */
	public void update() {
		repaint();
	}
}
