package timer;

import utils.Observable;

import java.util.Timer;
import java.util.TimerTask;

public class StopWatch extends Observable {
	private static int interval = 15;

	private Timer timer;
	private long time = 0;

	public void start() {
		if (timer != null) return;
		timer = new Timer(true);
		timer.scheduleAtFixedRate(ticker(), 0, interval);
	}

	private TimerTask ticker() {
		return new TimerTask() {
			public void run() {
				tick();
			}
		};
	}

	private void tick() {
		time += interval;
		notifyObservers();
	}

	public void stop() {
		if (timer == null) return;
		timer.cancel();
		timer = null;
	}

	public long getTime() {
		return time;
	}

	public void reset() {
		time = 0;
		notifyObservers();
	}

	public void toggle() {
		if (timer == null) start();
		else stop();
	}
}
