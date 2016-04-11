import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;
import java.util.Random;

public abstract class Figure implements Bouncable {
	private Display display = Display.getInstance();

	private double x, y;
	private double dx, dy;
	private double size;

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

	@Override
	public void draw() {
		getRenderer().display(display.getGraphics(), this);
	}

	@Override
	public void move() {
		x += dx;
		y += dy;

		int w = display.getWidth(), h = display.getHeight();

		if (x + size > w) {
			dx = -dx;
			x = w - size;
		} else if (x < 0) {
			dx = -dx;
			x = 0;
		}

		if (y + size > h) {
			dy = -dy;
			y = h - size;
		} else if (y < 0) {
			dy = -dy;
			y = 0;
		}
	}

	interface Filled extends Bouncable {
		Renderer RENDERER = new Renderer.Filled();

		default Renderable getRenderer() {
			return RENDERER;
		}
	}

	interface Bordered extends Bouncable {
		Renderer RENDERER = new Renderer.Bordered();

		default Renderable getRenderer() {
			return RENDERER;
		}
	}

	public static abstract class Square extends Figure {
		@Override
		public Shape getShape() { return new Rectangle2D.Double(getX(), getY(), getSize(), getSize()); }
	}

	public static class FilledSquare extends Square implements Filled {
		@Override
		public Color getColor() {
			return Color.ORANGE;
		}
	}

	public static class BorderedSquare extends Square implements Bordered {
		@Override
		public Color getColor() {
			return Color.RED;
		}
	}

	public static abstract class Circle extends Figure {
		@Override
		public Shape getShape() { return new Ellipse2D.Double(getX(), getY(), getSize(), getSize()); }
	}

	public static class FilledCircle extends Circle implements Filled {
		@Override
		public Color getColor() {
			return Color.BLUE;
		}
	}

	public static class BorderedCircle extends Circle implements Bordered {
		@Override
		public Color getColor() {
			return Color.GREEN;
		}
	}
}
