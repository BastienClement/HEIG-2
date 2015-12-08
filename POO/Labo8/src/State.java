/*
 * State.java
 *
 * @authors Bastien Clément et Alain Hardy
 * 8 décembre 2015
 */

import java.util.NoSuchElementException;
import java.util.Stack;

/**
 * Etat de la calculatrice (modèle).
 */
public class State {
	/**
	 * Pile interne de résultats
	 */
	private Stack<Double> stack = new Stack<>();

	/**
	 * Le dernier résultat calculé.
	 */
	private double result;

	/**
	 * Le nombre actuellement enregistré dans la mémoire.
	 * MemoryStore, MemoryRecall
	 */
	private double memory;

	/**
	 * L'entrée de l'utilisateur (éditable)
	 */
	private String input;

	/**
	 * L'erreur produite par la dernière opération.
	 */
	private String error;

	/**
	 * Flag indiquant si le prochain chiffre saisi sur
	 * le clavier doit implicitement push le dernier résultat
	 * sur la pile.
	 */
	private boolean shouldImplicitlyPush = false;

	// ========================================================================

	/**
	 * Constructeur, initialise correctement toutes les propriétés
	 */
	public State() { clearAll(); }

	/**
	 * Réinitialise entièrement l'état de la calculatrice.
	 * Associé à l'oppération "C"
	 */
	public void clearAll() {
		stack.clear();
		clearError();
		clearDisplay();
		memory = 0.0;
	}

	/**
	 * Réinitialise l'affichage de la calculatrice.
	 */
	public void clearDisplay() {
		result = 0.0;
		input = null;
	}

	// ========================================================================

	/**
	 * Retourne la chaine de texte à afficher sur l'écran de la calculatrice.
	 * - Si une erreur a été générée par la dernière opération,
	 * cette erreur sera afficheée
	 * - Si l'entrée de l'utilisateur est définie, elle est affichée.
	 * - Sinon, le dernier résultat est affiché en prenant soins de ne pas
	 * afficher le séparateur décimal (.) si ce résultat est entier.
	 *
	 * @return La chaîne de caractère à afficher
	 */
	public String getDisplayString() {
		if (error != null) {
			return error;
		} else if (input != null) {
			return input.length() == 0 ? "0" : input;
		} else {
			long ipart = (long) result;
			double fpart = result - ipart;
			return fpart == 0 ? Long.toString(ipart) : Double.toString(result);
		}
	}

	/**
	 * Retourne l'état actuel de la pile sous forme de tableau d'objets.
	 * Si la pile est vide, retourne un tableau contenant la chaine "<empty statck>"
	 *
	 * @return Le contenu de la pile
	 */
	public Object[] getStackArray() {
		if (stackSize() < 1) {
			return new String[]{"< empty stack >"};
		}

		int size = stack.size();
		Object[] arr = new Object[size];

		for (int i = 0; i < size; i++) {
			arr[size - i - 1] = Double.toString(stack.elementAt(i));
		}

		return arr;
	}

	// ========================================================================

	/**
	 * Retourne le résultat généré par la dernière opération.
	 * Si l'entrée utilisateur est définie, elle sera convertie en
	 * double et sa valeur sera retournée à la place du résultat.
	 *
	 * @return Le dernier résultat généré, ou l'entrée actuelle
	 */
	public double getResult() {
		if (input != null) return Double.valueOf(input);
		else return result;
	}

	/**
	 * Défini le résultat de la dernière opération.
	 * Réinitialise également le buffer d'entrée et défini le flag
	 * shouldImplicitlyPush.
	 *
	 * @param value Le résultat de la dernière opération
	 */
	public void setResult(Double value) {
		result = value;
		input = null;
		shouldImplicitlyPush = true;
	}

	// ========================================================================

	/**
	 * Retourne le buffer d'entrée actuel. Si celui-ci n'est pas défini,
	 * retourne à la place la chaîne vide.
	 *
	 * @return Le buffer d'entrée
	 */
	public String getInput() {
		return input == null ? "" : input;
	}

	/**
	 * Défini un nouveau buffer d'entrée utilisateur.
	 *
	 * @param i Le nouveau buffer d'entrée
	 */
	public void setInput(String i) {
		input = i;
	}

	// ========================================================================

	/**
	 * Pousse le résultat actuellement affiché à l'écran au sommet de la pile.
	 * Efface également le résultat affiché à l'écran.
	 * Associé à la touche Enter.
	 */
	public void pushResult() {
		stack.push(getResult());
		clearDisplay();
	}

	/**
	 * Tente de pousser implicitement le dernier résultat sur le sommet de la pile.
	 * Cette fonction est utilisée afin que le résultat d'une opération soit
	 * automatiquement ajouté à la pile lors de la saisie d'un chiffre après
	 * une opération.
	 */
	public void implicitlyPushResult() {
		if (!shouldImplicitlyPush) return;
		shouldImplicitlyPush = false;
		pushResult();
	}

	/**
	 * Supprime et retourne l'élément au sommet de la pile.
	 *
	 * @return L'élément au sommet de la pile.
	 */
	public double pop() {
		if (stack.isEmpty()) {
			throw new NoSuchElementException("Stack is empty");
		}
		return stack.pop();
	}

	/**
	 * Retourne le nombre d'élément sur la pile
	 */
	public int stackSize() {
		return stack.size();
	}

	// ========================================================================

	/**
	 * Défini la mémoire de la calculatrice.
	 *
	 * @param d La valeur à stocker dans la mémoire
	 */
	public void setMemory(double d) {
		memory = d;
	}

	/**
	 * Retourne la valeur stockée dans la mémoire.
	 *
	 * @return La valeur stockée
	 */
	public double getMemory() {
		return memory;
	}

	// ========================================================================

	/**
	 * Vérifie si la dernière opération a provoqué une erreur.
	 *
	 * @return true si la dernière oppération a provoqué une erreur
	 */
	public boolean hasError() {
		return error != null;
	}

	/**
	 * Défini le message d'erreur à afficher
	 *
	 * @param message Le message d'erreur
	 */
	public void setError(String message) {
		error = message;
	}

	/**
	 * Défini le message d'erreur sur la base d'une exception.
	 * La méthode getMessage() de l'exception sera appelée pour
	 * obtenir le message à afficher.
	 *
	 * @param exception L'exception
	 */
	public void setError(Exception exception) {
		setError(exception.getMessage());
	}

	/**
	 * Retourne le message d'erreur actuel.
	 *
	 * @return le message d'erreur
	 */
	public String getError() {
		return error;
	}

	/**
	 * Efface l'erreur actuelle.
	 */
	public void clearError() {
		error = null;
	}
}
