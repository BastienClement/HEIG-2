package gui;

import timer.StopWatch;
import utils.ClickListener;
import utils.Observer;

import javax.swing.*;

public class Clock extends JPanel implements Observer {
	protected StopWatch stopWatch;
	protected long time;

	public Clock(StopWatch sw) {
		stopWatch = sw;
		stopWatch.addObserver(this);
		addMouseListener((ClickListener)(e) -> stopWatch.toggle());
		update();
	}

	public void update() {
		time = stopWatch.getTime();
		repaint();
	}

	public void dispose() {
		stopWatch.removeObserver(this);
	}
}
