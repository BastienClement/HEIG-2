import gui.AnalogClock;
import gui.Clock;
import gui.ClockFace;
import gui.DigitalClock;
import timer.StopWatch;
import utils.ClickListener;
import utils.CloseListener;

import javax.swing.*;
import java.awt.*;

public class Labo01 {
	private static StopWatch sw = new StopWatch();

	public static void main(String[] args) {
		// Create main window and layout
		JFrame window = new JFrame();
		window.setLayout(new GridLayout(2, 1));

		// Clock-related buttons
		JPanel clocks_btns = new JPanel();
		clocks_btns.setLayout(new FlowLayout());
		addButton(clocks_btns, "Horloge romaine",   (e) -> openClock(new AnalogClock(ClockFace.ROMAN, sw)));
		addButton(clocks_btns, "Horloge arabe",     (e) -> openClock(new AnalogClock(ClockFace.ARABIC, sw)));
		addButton(clocks_btns, "Horloge numérique", (e) -> openClock(new DigitalClock(sw)));
		addButton(clocks_btns, "Horloge mixte",     (e) -> openClock(
				new AnalogClock(ClockFace.ROMAN, sw),
				new AnalogClock(ClockFace.ARABIC, sw),
				new DigitalClock(sw)
		));
		window.add(clocks_btns);

		// Timer-related buttons
		JPanel timer_btns = new JPanel();
		clocks_btns.setLayout(new FlowLayout());
		addButton(timer_btns, "Démarrer",      (e) -> sw.start());
		addButton(timer_btns, "Arreter",       (e) -> sw.stop());
		addButton(timer_btns, "Réinitialiser", (e) -> sw.reset());
		addButton(timer_btns, "Quitter",       (e) -> System.exit(0));
		window.add(timer_btns);

		// Display window
		window.pack();
		window.setVisible(true);
		window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	private static void addButton(Container container, String label, ClickListener listener) {
		JButton btn = new JButton(label);
		btn.addMouseListener(listener);
		container.add(btn);
	}

	private static void openClock(Clock... clocks) {
		JFrame window = new JFrame();
		window.setLayout(new FlowLayout());

		for (Clock clock : clocks) {
			window.add(clock);
		}

		window.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
		window.addWindowListener((CloseListener)(e) -> {
			for (Clock clock : clocks) {
				clock.dispose();
			}
		});

		window.pack();
		window.setVisible(true);
	}
}
