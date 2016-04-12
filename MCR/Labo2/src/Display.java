import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.image.BufferedImage;

/**
 * Affichage visuel.
 * Une seule action de cette classe est disponible dans l'application.
 */
public class Display extends JFrame implements Displayer {
	// Utilisation d'une classe interne dans le cas d'un accès concurrant à getInstance().
	private static class Singleton {
		private static final Display instance = new Display();
	}

	/**
	 * Retourne l'instance unique de cette classe.
	 */
	public static Display getInstance() {
		return Singleton.instance;
	}

	/**
	 * Utilisation d'une BufferedImage pour limiter les clignotements de l'affichage.
	 */
	private BufferedImage buffer;

	/**
	 * Constructeur privé.
	 */
	private Display() {
		setTitle("MCR: Labo 2");
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		setSize(600, 600);
		resetBuffer();
		setVisible(true);
	}

	/**
	 * Reset le buffer de dessin en créant une nouvelle image vierge.
	 */
	private void resetBuffer() {
		buffer = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g = getGraphics();
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, getWidth(), getHeight());
	}

	/**
	 * Retourne un objet Graphics2D pouvant être utilisé pour dessiner sur la fenêtre.
	 * Basé sur la BufferedImage plutôt que la JFrame.
	 */
	@Override
	public Graphics2D getGraphics() {
		return (Graphics2D) buffer.getGraphics();
	}

	/**
	 * Valide les dessins effectués sur l'image temporaire en la dessinant sur la fenêtre.
	 * L'image temporaire est réinitialisée à une image blanche.
	 */
	public void commit() {
		Graphics2D g = (Graphics2D) super.getGraphics();
		g.drawImage(buffer, 0, 0, null);
		resetBuffer();
	}

	/**
	 * Ajoute un KeyAdapter à cette fenêtre.
	 */
	@Override
	public void addKeyListener(KeyAdapter ka) {
		super.addKeyListener(ka);
	}
}
