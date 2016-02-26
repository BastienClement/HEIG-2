package gui;

import timer.StopWatch;

import java.awt.*;

public class AnalogClock extends Clock {
	private static final int CLOCK_SIZE = 300;

	ClockFace face;

	private int width, height;
	private Image img;

	public AnalogClock(ClockFace face, StopWatch sw) {
		super(sw);
		this.face = face;
		setPreferredSize(new Dimension(CLOCK_SIZE, CLOCK_SIZE));
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		int cur_width = getWidth();
		int cur_height = getHeight();

		if (img == null || width != cur_width || height != cur_height) {
			img = face.scaled(cur_width, cur_height);
			width = cur_width;
			height = cur_height;
		}

		g.drawImage(img, 0, 0, null);
		g.translate(CLOCK_SIZE / 2, CLOCK_SIZE / 2);

		double seconds = ((double) stopWatch.getTime()) / 1000;
		double minutes = seconds / 60;
		double hours   = seconds / 60 / 60;

		Graphics2D g2 = (Graphics2D) g;

		drawLine(g2, hours,   24, 6, CLOCK_SIZE / 5, 0x000000);
		drawLine(g2, minutes, 60, 4, CLOCK_SIZE / 3, 0x000000);
		drawLine(g2, seconds, 60, 2, CLOCK_SIZE / 3, 0xFF0000);
	}

	private void drawLine(Graphics2D g2, double val, double max, int width, int length, int color) {
		g2.setStroke(new BasicStroke(width));
		g2.setColor(new Color(color));
		double alpha = (val / max) * (Math.PI * 2);
		g2.drawLine(0, 0, (int) (Math.sin(alpha) * length), (int) (-Math.cos(alpha) * length));
	}
}
