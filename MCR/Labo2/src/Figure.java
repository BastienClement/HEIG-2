import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.util.Random;

/**
 * Classe de base des formes affichées à l'écran
 */
public abstract class Figure implements Bouncable {
	/** Sauvegerde d'une référence vers l'affichage */
	private Display display = Display.getInstance();

	/** Position x, y de la forme */
	private double x, y;

	/** Vecteur de déplacement de la forme */
	private double dx, dy;

	/** Taille de la forme */
	private double size;

	/**
	 * Initialisation des propriétés à des valeurs aléatoires.
	 */
	public Figure() {
		Random rand = new Random();
		x = rand.nextDouble() * display.getWidth();
		y = rand.nextDouble() * display.getHeight();
		dx = rand.nextDouble() * 6 - 3;
		dy = rand.nextDouble() * 6 - 3;
		size = rand.nextDouble() * 10 + 5;
	}

	public double getX() { return x; }
	public double getY() { return y; }
	public double getSize() { return size; }

	/**
	 * Dessine la forme sur l'affichage.
	 */
	@Override
	public void draw() {
		getRenderer().display(display.getGraphics(), this);
	}

	/**
	 * Déplace la forme en fonction du vecteur de déplacement.
	 */
	@Override
	public void move() {
		x += dx;
		y += dy;

		int w = display.getWidth(), h = display.getHeight();

		// On s'assure de pas dépasser les bords sur l'axe X
		if (x + size > w) {
			dx = -dx;
			x = w - size;
		} else if (x < 0) {
			dx = -dx;
			x = 0;
		}

		// On s'assure de pas dépasser les bords sur l'axe Y
		if (y + size > h) {
			dy = -dy;
			y = h - size;
		} else if (y < 0) {
			dy = -dy;
			y = 0;
		}
	}

	/**
	 * Interface utilisée pour injecter un Renderer "Filled" dans une forme.
	 * Sans cette classe, il aurait été nécessaire de définir deux fois getRenderer()
	 * dans les classes FilledSquare et FilledCircle. D'une certaines façon, nous avons
	 * ici un héritage simultané d'une forme particulière et de Filled.
	 */
	private interface Filled extends Bouncable {
		Renderer RENDERER = new Renderer.Filled();
		default Renderable getRenderer() {
			return RENDERER;
		}
	}

	/**
	 * Interface utilisée pour injecter un Renderer "Bouncable" dans une forme.
	 */
	private interface Bordered extends Bouncable {
		Renderer RENDERER = new Renderer.Bordered();
		default Renderable getRenderer() {
			return RENDERER;
		}
	}

	/**
	 * Classe de base d'un carré
	 */
	public static abstract class Square extends Figure {
		@Override
		public Shape getShape() { return new Rectangle2D.Double(getX(), getY(), getSize(), getSize()); }
	}

	/**
	 * Un carré rempli
	 */
	public static class FilledSquare extends Square implements Filled {
		@Override
		public Color getColor() {
			return Color.ORANGE;
		}
	}

	/**
	 * Un carré avec bordure
	 */
	public static class BorderedSquare extends Square implements Bordered {
		@Override
		public Color getColor() {
			return Color.RED;
		}
	}

	/**
	 * Classe de base d'une cercle
	 */
	public static abstract class Circle extends Figure {
		@Override
		public Shape getShape() { return new Ellipse2D.Double(getX(), getY(), getSize(), getSize()); }
	}

	/**
	 * Cercle rempli
	 */
	public static class FilledCircle extends Circle implements Filled {
		@Override
		public Color getColor() {
			return Color.BLUE;
		}
	}

	/**
	 * Cercle avec bordure
	 */
	public static class BorderedCircle extends Circle implements Bordered {
		@Override
		public Color getColor() {
			return Color.GREEN;
		}
	}
}
