package gui;

import timer.StopWatch;
import utils.ClickListener;
import utils.Observer;

import javax.swing.*;

public class Clock extends JPanel implements Observer {
	protected StopWatch stopWatch;

	public Clock(StopWatch sw) {
		stopWatch = sw;
		stopWatch.addObserver(this);
		addMouseListener((ClickListener)(e) -> stopWatch.toggle());
		update();
	}

	public void update() {
		repaint();
	}

	public void dispose() {
		stopWatch.removeObserver(this);
	}
}
