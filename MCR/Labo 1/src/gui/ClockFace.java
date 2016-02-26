package gui;

import javax.imageio.ImageIO;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public enum ClockFace {
	ARABIC("clock1.jpg"),
	ROMAN("clock2.jpg");

	/** The image corresponding to the ClockFace */
	private Image img;

	ClockFace(String path) {
		try {
			img = ImageIO.read(new File(path));
		} catch (IOException e) {
			throw new ExceptionInInitializerError(e);
		}
	}

	public Image scaled(int width, int height) {
		return img.getScaledInstance(width, height, Image.SCALE_SMOOTH);
	}
}
