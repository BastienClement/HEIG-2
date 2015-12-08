/*
 * ConsoleCalulator.java
 *
 * @authors Bastien Clément et Alain Hardy
 * 8 décembre 2015
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;

/**
 * Calculatrice en ligne de commande
 */
public class ConsoleCalculator {
	/**
	 * Permet la lecture de l'entrée console ligne par ligne.
	 */
	private BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

	/**
	 * Objet State représantant l'état de la calculatrice.
	 */
	private State state = new State();

	/**
	 * Association des commandes textuelles aux opérateurs disponibles.
	 */
	private HashMap<String, Operator> operators = new HashMap<>();

	/**
	 * Constructeur de la calculatrice en mode console.
	 * Initialise les opérateurs disponibles.
	 *
	 * @param args Les paramètres reçus depuis la ligne de commande
	 */
	public ConsoleCalculator(String... args) {
		operators.put("+", new Operator.Add(state));
		operators.put("-", new Operator.Subtract(state));
		operators.put("*", new Operator.Multiply(state));
		operators.put("/", new Operator.Divide(state));
		operators.put("sqrt", new Operator.SquareRoot(state));
		operators.put("^2", new Operator.Square(state));
		operators.put("inverse", new Operator.Inverse(state));
		operators.put("+/-", new Operator.Opposite(state));
		operators.put("clear", new Operator.Clear(state));
		operators.put("memset", new Operator.MemoryStore(state));
		operators.put("memget", new Operator.MemoryRecall(state));
	}

	/**
	 * Boucle principale de la calculatrice
	 */
	public void run() {
		String input;
		while ((input = prompt()) != null) {
			// Quitte la calculatrice lors d'une
			// entrée "exit"
			if (input.equals("exit")) break;

			// Evaluation de l'entrée
			evaluate(input);

			// Vérification si la calculatrice est dans un état d'erreur.
			// L'erreur est automatiquement effacée.
			if (state.hasError()) {
				System.out.println("* ERROR: " + state.getError());
				state.clearError();
			}

			// On affiche la valeur actuelle de l'affichage
			System.out.print(state.getResult());
			System.out.print(" ");

			// Puis tous les éléments de la pile
			if (state.stackSize() > 0) {
				for (Object value : state.getStackArray()) {
					System.out.print(value);
					System.out.print(" ");
				}
			}

			System.out.println();
		}
	}

	/**
	 * Evalue une ligne d'entrée.
	 * Peut être soit un opérateur, soit un nombre à ajouter sur la pile.
	 *
	 * @param line La ligne à évaluer
	 */
	public void evaluate(String line) {
		// On vérifie si c'est un opérateur
		if (operators.containsKey(line)) {
			Operator op = operators.get(line);
			op.execute();
			return;
		}

		// On considère l'entrée comme un nombre
		try {
			double value = Double.parseDouble(line);
			state.implicitlyPushResult();
			state.setResult(value);
		} catch (NumberFormatException e) {
			state.setError("Invalid input...");
		}
	}

	/**
	 * Lecture de l'entrée utiisateur.
	 *
	 * @return La commande saisie par l'utilisateur, null en cas d'erreur
	 */
	private String prompt() {
		System.out.print("> ");
		try {
			return reader.readLine();
		} catch (IOException e) {
			return null;
		}
	}

	/**
	 * Fonction principale lors de l'execution de la calculatrice en
	 * ligne de commandes.
	 *
	 * @param args Les arguments passés depuis la ligne de commande
	 */
	public static void main(String... args) {
		ConsoleCalculator calculator = new ConsoleCalculator(args);
		calculator.run();
	}
}
