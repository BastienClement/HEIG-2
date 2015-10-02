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

using namespace std;

template<typename GraphType>
class DirectedCycle {
private:
	bool hasCycle;
	list<int> cycle;
	
public:
	//constructeur
	DirectedCycle(const GraphType& g) {
		hasCycle = false;
		vector<bool> visited(g.V(), false);
		stack<int> s;

		for (int i = 0; i < g.V() && !hasCycle; i++) {
			if (visited.at(i)) continue;
			s.push(i);

			while (!s.empty()) {
				int v = s.top();
				s.pop();

				cycle.push_back(v);

				if (visited.at(v)) {
					hasCycle = true;
					break;
				} else {
					visited.at(v) = true;
				}

				for (auto a : g.adjacent(v)) {
					s.push(a);
				}
			}

			break;
		}

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
