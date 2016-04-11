
public abstract class BouncableFactory {
	public abstract Bouncable newSquare();
	public abstract Bouncable newCircle();

	public static class Bordered extends BouncableFactory {
		@Override
		public Bouncable newSquare() {
			return new Figure.BorderedSquare();
		}

		@Override
		public Bouncable newCircle() {
			return new Figure.BorderedCircle();
		}
	}

	public static class Filled extends BouncableFactory {
		@Override
		public Bouncable newSquare() {
			return new Figure.FilledSquare();
		}

		@Override
		public Bouncable newCircle() {
			return new Figure.FilledCircle();
		}
	}
}
