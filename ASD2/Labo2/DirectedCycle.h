/*
 * File:   DirectedCycle.h
 * Author: Olivier Cuisenaire
 * Modifier by: Bastien Cl�ment / Alain Hardy
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
	bool hasCycle; // Valeur d�finissant si le graphe poss�de un cycle
	vector<bool> marked; // Tableau permettant de savoir si un sommet a d�j� �t� visit�
	vector<bool> stacked; // Tableau permettant de savoir si un sommet a d�j� �t� ajout� � la pile
	stack<int> vstack; // Pile de parcours des sommets
	list<int> cycle; // Liste des sommets formant le cycle

	void DetectCycle(const GraphType& g, int v) {
		// Le sommet de d�part est marqu� et ajout� � la pile
		marked.at(v) = true;
		stacked.at(v) = true;
		vstack.push(v);

		// Pour chaque sommet adjacent
		for (int w : g.adjacent(v)) {
			// Si le graphe pr�sente un cycle, fin de la fonction
			if (hasCycle) {
				return;
			}
			// Si le sommet adjacent n'est pas d�j� visit�, on le visite
			else if (!marked.at(w)) {
				DetectCycle(g, w);
			}
			// Si le sommet adjacent est d�j� marqu�, cela veut dire qu'un cycle existe dans le graphe. On d�pile alors
			//  tous les sommet pr�sent dans la pile jusqu'au sommet �tant le d�but du cycle, c'est � dire le sommet
			//  empil� que l'on vient de d�tecter. Les sommets d�pil�s sont ajout�s � une liste fait �tat de tous les
			//  sommets pr�sents dans le cycle. Le sommet de d�but est � nouveau ajout� � la fin pour bien montr� le
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

		// Si un cycle a �t� d�tect� la fonction se termine
		if (hasCycle) return;


		// Le sommet ayant �t� trait� est d�pil�
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
