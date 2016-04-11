import java.awt.*;

public interface Bouncable {
	void draw();
	void move();
	Renderable getRenderer();
	Color getColor();
	Shape getShape();
}
