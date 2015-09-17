//
//  bfs.cpp
//
//  Created by Olivier Cuisenaire on 24.05.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include "Graph.h"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

const int nil = numeric_limits<int>::max();

vector<int> ParentsBFS(const Graph& g, int v) {
	vector<int> Parents(g.V(), nil);
	queue<int> Q;

	Q.push(v);
	Parents[v] = v;

	while (!Q.empty()) {
		const int v = Q.front();
		Q.pop();
		for (int w : g.adjacent(v)) {
			if (Parents[w] == nil) {
				Q.push(w);
				Parents[w] = v;
			}
		}
	}

	return Parents;
};

vector<int> PathBFS(vector<int> parents, int v) {
	vector<int> chemin;

	if (parents[v] == nil) {
		return chemin;
	}

	chemin.push_back(v);

	while (parents[v] != v) {
		v = parents[v];
		chemin.push_back(v);
	}

	return chemin;
}

void teste(const Graph& G, int v) {

	vector<int> parents = ParentsBFS(G, v);
	for (int w = 0; w < G.V(); ++w) {
		vector<int> chemin = PathBFS(parents, w);
		cout << w << " - " << v << ": ";
		if (chemin.empty()) {
			cout << "N/A";
		} else {
			for (int x : chemin) {
				cout << x << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

	Graph G(7);
	G.addEdge(0, 1);
	G.addEdge(1, 2);
	G.addEdge(2, 3);
	G.addEdge(3, 4);
	G.addEdge(4, 5);
	G.addEdge(5, 6);
	G.addEdge(6, 0);

	cout << "testing loop of 7 vertices \n\n";

	teste(G, 0);
	teste(G, 4);

	cout << "testing tinyG.txt... \n\n";
	ifstream s("tinyG.txt");
	teste(Graph(s), 0);
	s.close();

	cout << "testing mediumG.txt... \n\n";
	s.open("mediumG.txt");
	teste(Graph(s), 42);
	s.close();
}
