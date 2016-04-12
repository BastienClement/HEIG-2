import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.LinkedList;

/**
 * Application du Labo 2.
 */
public class BounceApp {
	/** Listes des bouncable affichés. */
	private final LinkedList<Bouncable> bouncers = new LinkedList<>();

	/** Référence vers l'objet singleton Display. */
	private Display display = Display.getInstance();

	public BounceApp() {
		display.addKeyListener(new AppKeyAdapter());
	}

	/**
	 * Boucle principale de l'application
	 */
	public void loop() {
		try {
			//noinspection InfiniteLoopStatement
			while (true) {
				synchronized (bouncers) {
					// Mise à jour et dessin de chaque bouncable
					bouncers.forEach(bouncable -> {
						bouncable.move();
						bouncable.draw();
					});
				}
				// Mise à jour de l'affichage
				display.commit();
				// 60 fps
				Thread.sleep(1000 / 60);
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	public static void main(String... args) {
		new BounceApp().loop();
	}

	/**
	 * Un KeyAdapter spécifique pour cette application.
	 * Les actions sont celles spécifiées dans la donnée.
	 */
	private class AppKeyAdapter extends KeyAdapter {
		// Construction des deux fabriques utilisées
		BouncableFactory.Bordered bbf = new BouncableFactory.Bordered();
		BouncableFactory.Filled fbf = new BouncableFactory.Filled();

		public void keyTyped(KeyEvent e) {
			switch (e.getKeyChar()) {
				case 'e':
					bouncers.clear();
					break;
				case 'b':
					addBouncers(10, bbf);
					break;
				case 'f':
					addBouncers(10, fbf);
					break;
				case 'q':
					System.exit(0);
					break;
			}
		}

		/**
		 * Ajout de Bouncers sur l'affichage
		 * @param n nombre de Bouncer à ajouter
		 * @param factory factory à utiliser pour fabriquer les Bouncers
		 */
		private void addBouncers(int n, BouncableFactory factory) {
			synchronized (bouncers) {
				for (int i = 0; i < n; i++) {
					bouncers.add(factory.newCircle());
					bouncers.add(factory.newSquare());
				}
			}
		}
	}
}
