//
// Created by Bastien Clément on 12.06.15.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <iostream>

class Graph {
public:
	typedef std::vector<int> Vertices;

	Graph(std::istream& stream);           // creation a partir d'un fichier

	Graph(int V);                          // creation d'un graphe de V sommets
	// et 0 aretes. Utiliser addEdge pour
	// lui ajouter des aretes.

	void addEdge(int v, int w);            // ajoute une arête

	const Vertices& adjacent(int v) const; // voisins du sommet v

	int V() const;                         // ordre du graphe

private:
	std::vector<Vertices> adjacencyLists;
};

#endif //GRAPH_GRAPH_H
