/**
 * Labo 01 - Observer Pattern
 * ClockFace.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package gui;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;

/**
 * Les looks de l'horloge analogique
 */
public enum ClockFace {
	ARABIC("clock1.jpg"),
	ROMAN("clock2.jpg");

	/** L'image a affiché pour ce look */
	private Image img;

	ClockFace(String path) {
		try {
			img = ImageIO.read(new File(path));
		} catch (IOException e) {
			throw new ExceptionInInitializerError(e);
		}
	}

	/**
	 * Redimmensionne l'image de fond à la taille du composant
	 * @param width  Largeur souhaitée
	 * @param height Hauteur souhaitée
	 * @return
	 */
	public Image scaled(int width, int height) {
		return img.getScaledInstance(width, height, Image.SCALE_SMOOTH);
	}
}
