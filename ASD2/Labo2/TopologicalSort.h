/*
 * File:   TopologicalSort.h
 * Author: Olivier Cuisenaire
 *
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
		if (!marked.at(v)) {
			for (int w : graph.adjacent(v)) {
				DFS(w);
			}
			marked.at(v) = true;
			order.push_back(v);
		}
	}

public:
	//constructeur
	TopologicalSort(const GraphType & g) : graph(g), cycle(g), marked(g.V(), false) {
		if (!IsDAG()) throw "NOT A DAG";

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
