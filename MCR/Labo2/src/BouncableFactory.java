/**
 * Fabrique d'élément Bouncable.
 * Permet de fabriquer des carrés ou des ronds. Le type exacte des instances
 * n'est pas fixé.
 */
public abstract class BouncableFactory {
	public abstract Bouncable newSquare();
	public abstract Bouncable newCircle();

	/**
	 * Implémentation de la fabrique abstraite qui construit des formes avec bordure
	 */
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

	/**
	 * Implémentation de la fabrique abstraite qui construit des formes remplies
	 */
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
