import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.image.BufferedImage;

public class Display extends JFrame implements Displayer {
	private static class Singleton {
		private static final Display instance = new Display();
	}

	public static Display getInstance() {
		return Singleton.instance;
	}

	private BufferedImage buffer;

	private Display() {
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setSize(600, 600);
		resetBuffer();
		setVisible(true);
	}

	private void resetBuffer() {
		buffer = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
	}

	@Override
	public Graphics2D getGraphics() {
		return (Graphics2D) buffer.getGraphics();
	}

	public void commit() {
		Graphics2D g = (Graphics2D) super.getGraphics();
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, getWidth(), getHeight());
		g.drawImage(buffer, 0, 0, null);
		resetBuffer();
	}

	@Override
	public void addKeyListener(KeyAdapter ka) {
		super.addKeyListener(ka);
	}
}
