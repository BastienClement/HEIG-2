//
// Created by Bastien Clément on 12.06.15.
//

#include "graph.h"

using namespace std;

Graph::Graph(int V)
{
	adjacencyLists.resize(V);
}

Graph::Graph(istream& s) {
	int V,E,v,w;
	s >> V >> E;
	adjacencyLists.resize(V);

	for (int i = 0; i < E; i++) {
		s >> v >> w;
		addEdge(v, w);
	}
}

void Graph::addEdge(int v, int w) {
	adjacencyLists.at(v).push_back(w);
	if (v != w)
		adjacencyLists.at(w).push_back(v);
}

const Graph::Vertices& Graph::adjacent(int v) const {
	return adjacencyLists.at(v);
}

int Graph::V() const {
	return (int)adjacencyLists.size();
}
