import java.awt.*;

/**
 * Une interface qui aurait pu être nommée Renderer et causer moins de confusion.
 * S'occupe de dessiner une forme à l'écran, soit avec une bordure, soit remplie.
 */
public interface Renderable {
	void display(Graphics2D g, Bouncable b);
}
