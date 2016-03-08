package gui;

import timer.StopWatch;
import utils.ClickListener;
import utils.Observer;

import javax.swing.*;
import java.awt.*;

public abstract class Clock extends JPanel implements Observer {
	protected StopWatch stopWatch;

	public Clock(StopWatch sw) {
		stopWatch = sw;
		stopWatch.addObserver(this);
		addMouseListener((ClickListener)(e) -> stopWatch.toggle());
	}

	@Override
	protected void paintComponent(Graphics g) {
		update();
		super.paintComponent(g);
	}

	abstract public void update();

	public void dispose() {
		stopWatch.removeObserver(this);
	}
}
