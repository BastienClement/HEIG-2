/**
 * Labo 01 - Observer Pattern
 * ClickListener.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package utils;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public interface ClickListener extends MouseListener {
	//void mouseClicked(MouseEvent e);
	default void mousePressed(MouseEvent e) {}
	default void mouseReleased(MouseEvent e) {}
	default void mouseEntered(MouseEvent e) {}
	default void mouseExited(MouseEvent e) {}
}
