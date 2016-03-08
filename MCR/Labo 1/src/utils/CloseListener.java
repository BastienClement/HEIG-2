/**
 * Labo 01 - Observer Pattern
 * CloseListener.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package utils;

import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public interface CloseListener extends WindowListener {
	//void windowClosing(WindowEvent e);
	default void windowOpened(WindowEvent e) {}
	default void windowClosed(WindowEvent e) {}
	default void windowIconified(WindowEvent e) {}
	default void windowDeiconified(WindowEvent e) {}
	default void windowActivated(WindowEvent e) {}
	default void windowDeactivated(WindowEvent e) {}
}
