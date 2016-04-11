import java.awt.*;
import java.awt.event.KeyAdapter;

public interface Displayer {
	int getWidth();
	int getHeight();
	Graphics2D getGraphics();
	void repaint();
	void setTitle(String s);
	void addKeyListener(KeyAdapter ka);
	void commit();
}
