//
//  bfs.cpp
//
//  Created by Olivier Cuisenaire on 24.05.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

#include "Graph.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>

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

template <typename MFn, typename AFn>
void read_file(const MFn& cb_movie, const AFn& cb_actor) {
	string line;
	ifstream s("movies.txt");
	while (getline(s, line))
	{
		stringstream ss(line);

		string movie;
		getline(ss, movie, '/');
		cb_movie(movie);

		string actor;
		while (getline(ss, actor, '/')) {
			cb_actor(actor);
		}
	}
	s.close();
}

vector<int> path(const Graph& g, const unordered_map<string, int>& indices, string A, string B) {
	static vector<int> parents;
	static string origin = "";

	if (indices.count(A) == 0 || indices.count(B) == 0)
		throw "Sommet introuvable";

	if (A != origin) {
		parents = ParentsBFS(g, indices.at(A));
		origin = A;
	}

	return PathBFS(parents, indices.at(B));
}

int main() {
	unordered_map<int, string> labels;
	unordered_map<string, int> indices;
	int next_idx = 0;

	const auto create_symbol = [&](const string& sym) {
		if (indices.count(sym) == 0) {
			labels[next_idx] = sym;
			indices[sym] = next_idx++;
		}
	};

	read_file(create_symbol, create_symbol);

	Graph g(labels.size());
	int current_movie = nil;

	read_file([&](const string& movie) {
		current_movie = indices[movie];
	}, [&](const string& actor) {
		g.addEdge(current_movie, indices[actor]);
	});

	const string KEVIN_BACON = "Bacon, Kevin";

	while (true) {
		string start;
		cout << "Départ: ";
		getline(cin, start);

		if (start.empty()) break;

		if (start == "max") {
			int max = 0;
			int max_idx = 0;
			srand(time(NULL));
			for (const pair<string, int>& item : indices) {
				const int idx = item.second;
				const int d = path(g, indices, KEVIN_BACON, labels[idx]).size();
				if (d > max || (d == max && rand() % 2)) {
					max = d;
					max_idx = idx;
				}
			}
			start = labels[max_idx];
		}

		try {
			auto p = path(g, indices, KEVIN_BACON, start);
			cout << endl;
			for (const int& idx : p) {
				cout << labels[idx] << endl;
			}
			cout << endl << "DISTANCE = " << p.size() / 2 << endl;
		} catch (const char* err) {
			cout << err << endl;
		}

		cout << endl;
	}
}
