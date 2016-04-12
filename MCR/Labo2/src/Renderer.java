import java.awt.*;

/**
 * Implémentations de Renderable.
 * Défini deux implémentations dessinant les formes avec bordures ou remplies.
 */
public abstract class Renderer implements Renderable {
	/**
	 * Dessine les formes avec bordures
	 */
	public static class Bordered extends Renderer {
		@Override
		public void display(Graphics2D g, Bouncable b) {
			g.setStroke(new BasicStroke(2));
			g.setColor(b.getColor());
			g.draw(b.getShape());
		}
	}

	/**
	 * Dessine des formes remplies
	 */
	public static class Filled extends Renderer {
		@Override
		public void display(Graphics2D g, Bouncable b) {
			g.setColor(b.getColor());
			g.fill(b.getShape());
		}
	}
}
