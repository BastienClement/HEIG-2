import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.LinkedList;

public class BounceApp {
	private final LinkedList<Bouncable> bouncers = new LinkedList<>();
	private Display display = Display.getInstance();

	public BounceApp() {
		display.addKeyListener(new AppKeyAdapter());
	}

	public void loop() {
		try {
			//noinspection InfiniteLoopStatement
			while (true) {
				synchronized (bouncers) {
					bouncers.forEach(bouncable -> {
						bouncable.move();
						bouncable.draw();
					});
				}
				display.commit();
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

	private class AppKeyAdapter extends KeyAdapter {
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
