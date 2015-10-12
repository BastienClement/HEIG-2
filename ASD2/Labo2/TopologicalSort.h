/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 * Modifier by: Bastien Cl�ment / Alain Hardy *
 * Created on 08. octobre 2014, 14:07
 *
 * A implementer
 * Classe permettant le tri topologique d'un graphe oriente
 */

#ifndef ASD2_TopologicalSort_h
#define ASD2_TopologicalSort_h

#include "DirectedCycle.h"
#include <iostream>

template < typename GraphType >
class TopologicalSort {
private:
	const GraphType& graph;
	DirectedCycle<GraphType> cycle;
	std::vector<bool> marked;
	std::vector<int> order;

	void DFS(int v) {
		// Le traitement a lieu uniquement si le sommet n'est pas marqu�
		if (!marked.at(v)) {
			// Parcours de tous les sommets adjacent
			for (int w : graph.adjacent(v)) {
				DFS(w);
			}
			// Marquage du sommet
			marked.at(v) = true;
			// Comme le parcours DFS se fait sur le graphe invers�, il suffit d'ajouter le num�ro du sommet
			//  au retour de la r�cursion, � la fin du vecteur
			order.push_back(v);
		}
	}

public:
	//constructeur
	TopologicalSort(const GraphType & g) : graph(g), cycle(g), marked(g.V(), false) {
		// Contr�le de la pr�sence d'un cycle, si c'est le cas, le cycle sera r�cup�r� par le main via une exception
		//  de fa�on � pouvoir l'afficher par la suite
		if (!IsDAG()) throw cycle;

		// Parcours DFS de tous les sommets du graphe
		for (int i = 0; i < g.V(); i++) {
			DFS(i);
		}
	}

	//indique si le graphe est DAG (Directed Acyclic Graph))
	bool IsDAG() {
		return !cycle.HasCycle();
	}

	//tableau contenant l'ordre de parcours des indexes des sommets dans le graphe
	const std::vector<int>& Order() {
		return order;
	}
};

#endif
