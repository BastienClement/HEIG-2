/*
 * Operator.java
 *
 * @authors Bastien Clément et Alain Hardy
 * 8 décembre 2015
 */

/**
 * Un opérateur de la calculatrice
 */
public abstract class Operator {
	/**
	 * L'objet état que devra manipuler cet opérateur
	 */
	protected State state;

	/**
	 * Constructeur. Associe l'opérateur à un objet d'état spécifique.
	 *
	 * @param state L'état à manipuler par cet opérateur
	 */
	Operator(State state) {
		this.state = state;
	}

	/**
	 * Execute l'opérateur.
	 * <p>
	 * Cette méthode vérifie en premier lieu que l'opérateur
	 * peut être utilisé (méthode valid()) puis execute son
	 * comportement (méthode run()).
	 * <p>
	 * Si une exception est lancée par l'une de ces deux méthodes,
	 * l'erreur est enregistrée dans l'état de la calculatrice.
	 */
	public void execute() {
		try {
			if (valid()) run();
		} catch (Exception e) {
			state.setError(e);
		}
	}

	/**
	 * Vérifie de l'opérateur peut être executé dans l'état actuel
	 * de la calculatrice.
	 * <p>
	 * Par défaut, s'assure que la calculatrice ne soit pas en
	 * condition d'erreur.
	 *
	 * @return true si l'opérateur peut être executé, false sinon
	 * @throws Exception Les exceptions lancée par cette méthode seront
	 *                   affichée à l'utilisateur.
	 */
	protected boolean valid() throws Exception {
		return !state.hasError();
	}

	/**
	 * Execute réellement l'opérateur.
	 *
	 * @throws Exception De même que valid()...
	 */
	protected abstract void run() throws Exception;

	// ========================================================================

	/**
	 * Classe utilitaire de base pour un opérateur unaire.
	 * <p>
	 * Au lieu d'implémenter run(), les classes dérivées doivent
	 * implémenter op(double a) qui prend en paramètre l'opérande
	 * de l'opérateur et retourne le résultat.
	 */
	public abstract static class UnaryOperator extends Operator {
		public UnaryOperator(State state) { super(state); }

		/**
		 * Effectue l'opération "op a"
		 *
		 * @param a Opérande de l'opérateur
		 * @return Résultat de l'opérateur
		 */
		abstract protected double op(double a);

		/**
		 * Implémente le comportement général d'un opérateur unaire.
		 */
		protected void run() {
			double a = state.getResult();
			double r = op(a);
			state.setResult(r);
		}
	}

	/**
	 * Classe utilitaire de base pour un opérateur binaire.
	 * <p>
	 * Au lieu d'implémenter run(), les classes dérivées doivent
	 * implémenter op(double a, double b) qui prend en paramètre
	 * les opérandes de l'opérateur et retourne le résultat.
	 */
	public abstract static class BinaryOperator extends Operator {
		public BinaryOperator(State state) { super(state); }

		/**
		 * Effectue l'opération "a op b"
		 *
		 * @param a Première opérande de l'opérateur
		 * @param b Deuxième opérande de l'opérateur
		 * @return Résultat de l'opérateur
		 */
		abstract protected double op(double a, double b);

		/**
		 * Pour être valide, une opération binaire requiert
		 * deux opérandes.
		 *
		 * @return true si au moins deux opérandes sont disponibles
		 * @throws Exception Si il n'y a pas assez d'opérandes disponibles
		 */
		protected boolean valid() throws Exception {
			if (state.stackSize() < 1) throw new Exception("Not enough operands");
			return super.valid();
		}

		/**
		 * Implémente le comportement général d'un opérateur binaire.
		 */
		protected void run() {
			double b = state.getResult();
			double a = state.pop();
			double r = op(a, b);
			state.setResult(r);
		}
	}

	/**
	 * Classe utilitaire de base pour un opérateur manipulant l'affichage.
	 * <p>
	 * Au lieu d'implémenter run(), les classes dérivées doivent
	 * implémenter apply(String input) qui prend en paramètre
	 * la valeur actuel du buffer d'entrée et retourne sa nouvelle valeur.
	 */
	public abstract static class DisplayOperator extends Operator {
		public DisplayOperator(State state) { super(state); }

		/**
		 * Transforme le buffer d'entrée utilisateur pour y appliquer
		 * l'opérateur.
		 *
		 * @param input Le buffer actuel
		 * @return La nouvelle valeur du buffer d'entrée
		 */
		abstract protected String apply(String input);

		/**
		 * Implémente le comportement général d'un opérateur d'affichage.
		 */
		protected void run() {
			state.implicitlyPushResult();
			String input = state.getInput();
			String result = apply(input);
			state.setInput(result);
		}
	}

	// ========================================================================

	/**
	 * Addition
	 */
	public static class Add extends BinaryOperator {
		public Add(State state) { super(state); }
		protected double op(double a, double b) { return a + b; }
	}

	/**
	 * Soustraction
	 */
	public static class Subtract extends BinaryOperator {
		public Subtract(State state) { super(state); }
		protected double op(double a, double b) { return a - b; }
	}

	/**
	 * Multiplication
	 */
	public static class Multiply extends BinaryOperator {
		public Multiply(State state) { super(state); }
		protected double op(double a, double b) { return a * b; }
	}

	/**
	 * Division
	 * Note: la division par zéro n'est pas gérée comme cas particulier
	 * et produit un résultat NaN comme défini par l'arithmétique des
	 * nombres à virgule flottante.
	 */
	public static class Divide extends BinaryOperator {
		public Divide(State state) { super(state); }
		protected double op(double a, double b) { return a / b; }
	}

	// ========================================================================

	/**
	 * Racine carrée
	 */
	public static class SquareRoot extends UnaryOperator {
		public SquareRoot(State state) { super(state); }
		protected double op(double a) { return Math.sqrt(a); }
	}

	/**
	 * "X à la 2"
	 */
	public static class Square extends UnaryOperator {
		public Square(State state) { super(state); }
		protected double op(double a) { return a * a; }
	}

	/**
	 * L'inverse d'un nombre
	 */
	public static class Inverse extends UnaryOperator {
		public Inverse(State state) { super(state); }
		protected double op(double a) { return 1.0 / a; }
	}

	/**
	 * L'opposé d'un nombre
	 */
	public static class Opposite extends UnaryOperator {
		public Opposite(State state) { super(state); }
		protected double op(double a) { return -a; }
	}

	// ========================================================================

	/**
	 * Réinitialise la calculatrice
	 * Cette opération est toujours disponible
	 */
	public static class Clear extends Operator {
		public Clear(State state) { super(state); }
		protected boolean valid() { return true; }
		protected void run() { state.clearAll(); }
	}

	/**
	 * Efface l'erreur actuellement affichée
	 * Cette opération est toujours disponible
	 */
	public static class ClearError extends Operator {
		public ClearError(State state) { super(state); }
		protected boolean valid() { return true; }
		protected void run() { state.clearError(); }
	}

	// ========================================================================

	/**
	 * Récupère la valeur enregistrée dans la mémoire
	 */
	public static class MemoryRecall extends Operator {
		public MemoryRecall(State state) { super(state); }
		protected void run() { state.setResult(state.getMemory()); }
	}

	/**
	 * Enregistre la valeur courante dans la mémoire
	 */
	public static class MemoryStore extends Operator {
		public MemoryStore(State state) { super(state); }
		protected void run() { state.setMemory(state.getResult()); }
	}

	/**
	 * Pousse la valeur courante sur la pile
	 */
	public static class Enter extends Operator {
		public Enter(State state) { super(state); }
		protected void run() { state.pushResult(); }
	}

	// ========================================================================

	/**
	 * Retour arrière
	 */
	public static class Backspace extends DisplayOperator {
		public Backspace(State state) { super(state); }

		protected String apply(String input) {
			if (!input.isEmpty()) input = input.substring(0, input.length() - 1);
			return input;
		}
	}

	/**
	 * Chiffre
	 */
	public static class Digit extends DisplayOperator {
		/**
		 * La caractère correspondant à ce chiffre
		 * Le point étant traité comme un chiffre, il n'est pas possible
		 * d'utiliser un type int ici.
		 */
		char digit;

		/**
		 * Constructeur.
		 *
		 * @param state L'état manipulé par cet opérateur
		 * @param digit Le chiffre à ajouter au buffer d'entrée lors de
		 *              l'execution de cette opération.
		 */
		public Digit(State state, char digit) {
			super(state);
			this.digit = digit;
		}

		/**
		 * Ajoute le chiffre à la suite du buffer d'entrée.
		 */
		protected String apply(String input) {
			return input + digit;
		}
	}

	/**
	 * Cas particulier du zéro.
	 * Il n'est pas possible d'insérer un zéro en début de nombre.
	 */
	public static class Zero extends Digit {
		public Zero(State state) { super(state, '0'); }

		protected boolean valid() throws Exception {
			return !state.getInput().isEmpty() && super.valid();
		}
	}

	/**
	 * Cas particulier du point.
	 * Il n'est pas possible d'insérer plus d'un point.
	 * De plus, si le point est le premier caractère inséré, un
	 * 0 est automatiquement ajouté avant.
	 */
	public static class Dot extends Digit {
		public Dot(State state) { super(state, '.'); }

		protected boolean valid() throws Exception {
			return state.getInput().indexOf('.') == -1 && super.valid();
		}

		protected String apply(String input) {
			return super.apply(input.isEmpty() ? "0" : input);
		}
	}
}

