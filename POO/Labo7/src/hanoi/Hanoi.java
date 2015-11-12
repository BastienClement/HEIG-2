/*
 * Fichier 	: Hanoi.java
 * Date		: 29.10.2015
 * But 		: Permet la résolution et l'affichage du problème des tours de Hanoï.
 * Auteur	: Bastien Clément / Alain Hardy
 */

package hanoi;

import hanoi.gui.JHanoi;
import util.Stack;

import java.util.Iterator;

/**
 * Résolution du problème des tours de Hanoi
 */
public class Hanoi {
    @SuppressWarnings("unchecked")
    Stack<Integer>[] sticks = new Stack[3];

    int turn = -1;
    boolean finished = false;

    public Hanoi(int h) {
        // Construction des piquets
        for (int i = 0; i < 3; i++) {
            sticks[i] = new Stack<Integer>();
        }

        // Empilement des disques sur le premier piquet
        for (; h > 0; h--) {
            sticks[0].push(h);
        }
    }

    /**
     * Initialise la résolution du problème.
     */
    public void solve(JHanoi frame) {
        if (finished) return;

        printStep();
        if (frame != null) frame.display();

        resolve(frame, sticks[0].size(), sticks[0], sticks[2], sticks[1]);
        finished = true;
    }

    /**
     * Résolution récursive du problème des tours de Hanoi
     * int n : Nombre de disque à déplacer
     * Stack<Integer> D : Pile de départ
     * Stack<Integer> A : Pile d'arrivée
     * Stack<Integer> I : Pile intermédiare
     * 
     * Dans un premier temps, il faut déplacer les disques de la colonne de départ dans la colonne intermédiaire,
     * en se servant de la colonne d'arrivée comme de colonne intermédiaire, afin de pouvoir mettre le plus grand 
     * disque dans la colonne d'arrivée. À partir de là, il faut déplacer les  disques de la colonne intermédiaire 
     * à la colonne d'arrivée en se servant de la colonne de départ comme de colonne intermédiaire.
     */
    private void resolve(JHanoi frame, int n, Stack<Integer> D, Stack<Integer> A, Stack<Integer> I) {
        if (n == 0) return;

        resolve(frame, n - 1, D, I, A);

        A.push(D.pop());
        
        printStep();
        if (frame != null) frame.display();
        
        resolve(frame, n - 1, I, A, D);
    }

    /**
     * Affiche l'étape actuelle de la résolution sous
     * forme textuelle.
     */
    private void printStep() {
        System.out.println("-- Turn: " + ++turn);
        System.out.println(this);
    }

    /**
     * Retourne une représentation textuelle de l'état courrant
     * des différents piquets.
     */
    public String toString() {
        String s = "One:\t" + sticks[0] + "\n";
        s += "Two:\t" + sticks[1] + "\n";
        s += "Three:\t" + sticks[2] + "\n";

        return s;
    }

    /**
     * Retourne une représentation sous forme de tableau des
     * différents piquets.
     * Note: il n'est pas possible d'utiliser la fonction Stack.toArray()
     * puisque les types des tableaux ne sont pas les mêmes.
     */
    public int[][] status() {
        int[][] t = new int[3][];

        for (int i = 0; i < 3; i++) {
            Stack<Integer> stick = sticks[i];
            t[i] = new int[stick.size()];
            Iterator<Integer> it = stick.iterator();
            for (int j = 0; it.hasNext(); j++) {
                t[i][j] = it.next();
            }
        }

        return t;
    }

    /**
     * Indique si la résolution du problème est terminée
     */
    public boolean finished() {
        return finished;
    }

    /**
     * Retourne le nombre de déplacement effectués
     */
    public int turn() {
        return turn;
    }

    /**
     * Fonction principale
     */
    public static void main(String[] args) {
        if (args.length > 0) {
            // Lancement en mode console si un argument est passé
            int s = Integer.parseInt(args[0]);
            Hanoi h = new Hanoi(s);
            h.solve(null);
        } else {
            // Lancement en mode graphique
            new JHanoi();
        }
    }
}
