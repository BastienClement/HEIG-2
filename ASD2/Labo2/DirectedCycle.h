/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
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
	bool hasCycle;
	vector<bool> marked;
	vector<bool> stacked;
	stack<int> vstack;
	list<int> cycle;

	void DetectCycle(const GraphType& g, int v) {
		marked.at(v) = true;
		stacked.at(v) = true;
		vstack.push(v);

		for (int w : g.adjacent(v)) {
			if (hasCycle) {
				return;
			} else if (!marked.at(w)) {
				DetectCycle(g, w);
			} else if (stacked.at(w)) {
				hasCycle = true;
				int a;
				do {
					a = vstack.top();
					vstack.pop();
					cycle.push_front(a);
				} while (a != w);
			}
		}

		if (hasCycle) return;

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
