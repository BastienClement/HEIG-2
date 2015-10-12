/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Modifier by: Bastien Clément / Alain Hardy
 * Created on 08. octobre 2014, 10:46
 *
 * A implementer
 * Classe permettant la detection de cycle sur un graphe oriente
 */

#ifndef ASD2_DirectedCycle_h
#define ASD2_DirectedCycle_h

#include <vector>
#include <stack>
#include <list>
#include <iostream>

using namespace std;

template<typename GraphType>
class DirectedCycle {
private:
	bool hasCycle; // Valeur définissant si le graphe possède un cycle
	vector<bool> marked; // Tableau permettant de savoir si un sommet a déjà été visité
	vector<bool> stacked; // Tableau permettant de savoir si un sommet a déjà été ajouté à la pile
	stack<int> vstack; // Pile de parcours des sommets
	list<int> cycle; // Liste des sommets formant le cycle

	void DetectCycle(const GraphType& g, int v) {
		// Le sommet de départ est marqué et ajouté à la pile
		marked.at(v) = true;
		stacked.at(v) = true;
		vstack.push(v);

		// Pour chaque sommet adjacent
		for (int w : g.adjacent(v)) {
			// Si le graphe présente un cycle, fin de la fonction
			if (hasCycle) {
				return;
			}
			// Si le sommet adjacent n'est pas déjà visité, on le visite
			else if (!marked.at(w)) {
				DetectCycle(g, w);
			}
			// Si le sommet adjacent est déjà marqué, cela veut dire qu'un cycle existe dans le graphe. On dépile alors
			//  tous les sommet présent dans la pile jusqu'au sommet étant le début du cycle, c'est à dire le sommet
			//  empilé que l'on vient de détecter. Les sommets dépilés sont ajoutés à une liste fait état de tous les
			//  sommets présents dans le cycle. Le sommet de début est à nouveau ajouté à la fin pour bien montré le
			//  cycle.
			else if (stacked.at(w)) {
				hasCycle = true;
				int a;
				do {
					a = vstack.top();
					vstack.pop();
					cycle.push_back(a);
				} while (a != w);
				cycle.push_back(cycle.front());
			}
		}

		// Si un cycle a été détecté la fonction se termine
		if (hasCycle) return;


		// Le sommet ayant été traité est dépilé
		stacked.at(v) = false;
		vstack.pop();
	}

public:
	//constructeur
	DirectedCycle(const GraphType& g): marked(g.V(), false), stacked(g.V(), false), hasCycle(false) {
		DetectCycle(g, 0);
	}

	//indique la presence d'un cycle
	bool HasCycle() {
		return hasCycle;
	}

	//liste les indexes des sommets formant une boucle
	const list<int>& Cycle() {
		return cycle;
	}

};

#endif
