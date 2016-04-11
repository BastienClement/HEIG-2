import java.awt.*;

public abstract class Renderer implements Renderable {
	public static class Bordered extends Renderer {
		@Override
		public void display(Graphics2D g, Bouncable b) {
			g.setStroke(new BasicStroke(2));
			g.setColor(b.getColor());
			g.draw(b.getShape());
		}
	}

	public static class Filled extends Renderer {
		@Override
		public void display(Graphics2D g, Bouncable b) {
			g.setColor(b.getColor());
			g.fill(b.getShape());
		}
	}
}
