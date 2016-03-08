/**
 * Labo 01 - Observer Pattern
 * Observer.java
 *
 * @author Bastien Clément
 * @author Alain Hardy
 */

package utils;

/**
 * Un observateur
 */
public interface Observer {
	/**
	 * Méthode appelée lorsque l'état du sujet change
	 */
	void update();
}
