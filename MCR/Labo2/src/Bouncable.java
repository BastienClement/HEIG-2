import java.awt.*;

/**
 * Un Bouncable est un objet affichable dans l'application qui rebondit sur les bords
 * de la fenêtre.
 */
public interface Bouncable {
	void draw();
	void move();
	Renderable getRenderer();
	Color getColor();
	Shape getShape();
}
