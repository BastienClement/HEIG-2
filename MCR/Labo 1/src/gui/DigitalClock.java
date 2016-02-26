package gui;

import timer.StopWatch;

import javax.swing.*;
import java.awt.*;

public class DigitalClock extends Clock {
	JLabel label = new JLabel("00:00:00.0");

	public DigitalClock(StopWatch sw) {
		super(sw);
		add(label);
	}

	public void paintComponent(Graphics g) {
		long time = stopWatch.getTime();

		long millis  = time % 1000;
		long seconds = (time /= 1000) % 60;
		long minutes = (time /= 60) % 60;
		long hours   = (time / 60) % 24;

		label.setText(String.format("%02d:%02d:%02d.%01d", hours, minutes, seconds, millis / 100));
	}
}
