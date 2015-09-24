//
//  bfs.cpp
//
//  Created by Olivier Cuisenaire on 24.05.15.
//  Copyright (c) 2015 Olivier Cuisenaire. All rights reserved.
//

/*
 * Labo 01 par
 *  Bastien Clément
 *  Alain Hardy
 *
 * Basé sur le labo du semestre passé par
 * 	Bastien Clément
 * 	Christophe Peretti
 * 	Arthur Verdon
 */

#include "Graph.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <time.h>

using namespace std;

// Valeur nulle de type int signifiant "aucune valeure"
const int nil = numeric_limits<int>::max();

// Assigne à chaque sommet un sommet parent qui est un degré plus proche du sommet de départ v
// construisant ainsi un chemin de retour vers le centre du graph
vector<int> ParentsBFS(const Graph& g, int v) {
	// Liste des parents de tous les sommets
	vector<int> Parents(g.V(), nil);

	// Queue utilisée pour le parcours en largeur
	queue<int> Q;

	// On commence par le sommet de départ
	Q.push(v);

	// Le sommet de départ est identifié en étant son propre parent
	// parent(v) == v
	Parents[v] = v;

	while (!Q.empty()) {
		// Sommet courant
		const int v = Q.front();
		Q.pop();

		// Parcours de tous les sommets adjacent
		for (int w : g.adjacent(v)) {
			// S'il n'a pas encore été visité
			if (Parents[w] == nil) {
				Q.push(w);

				// La parent de ce sommet est v (d'où l'on vient)
				Parents[w] = v;
			}
		}
	}

	return Parents;
};

// Suit les parents calculés par la fonction ParentsBFS pour fabriquer la
// la liste des sommets du sommet v jusqu'au centre du graph (paramètre v de ParentsBFS)
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

// Lis le fichier de données et appel les fonctions cb_movie et cb_actor à chaque fois qu'il rencontre
// un nom de film ou un nom d'acteur. L'utilisation de callbacks permet de modifier les effets de cette lecture.
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

// Calcul le chemin de A à B
vector<int> path(const Graph& g, const unordered_map<string, int>& indices, string A, string B) {
	// L'opération de calcul des parents pour tous les sommets du graph est longue.
	// On garde donc en cache le dernier calcul pour le cas où le point d'arrivée est le même
	// entre plusieurs appels de la fonction. (C'est le cas puisque c'est toujours Kevin Bacon)
	static vector<int> parents;
	static string origin = "";

	if (indices.count(A) == 0 || indices.count(B) == 0)
		throw "Sommet introuvable";

	// On vérifie si on doit recalculer les parents (le centre du graph n'est pas le même)
	if (A != origin) {
		parents = ParentsBFS(g, indices.at(A));
		origin = A;
	}

	return PathBFS(parents, indices.at(B));
}

int main() {
	// Association "no sommet" -> "label"
	unordered_map<int, string> labels;

	// Association "label" -> "no sommet"
	unordered_map<string, int> indices;

	// Numéro du prochain sommet créé
	int next_idx = 0;

	// Cette fonction crée un nouveau sommet pour le nom reçu en paramètre s'il n'en existe pas déjà un
	const auto create_symbol = [&](const string& sym) {
		if (indices.count(sym) == 0) {
			labels[next_idx] = sym;
			indices[sym] = next_idx++;
		}
	};

	// Création de tous les sommets du graph
	read_file(create_symbol, create_symbol);

	// Création du graph
	Graph g(labels.size());

	// Film actuel durant la lecture du fichier
	int current_movie = nil;

	read_file([&](const string& movie) {
		// Nouveau film, on modifie current_movie
		current_movie = indices[movie];
	}, [&](const string& actor) {
		// On ajoute une arête entre le film et l'acteur actuels
		g.addEdge(current_movie, indices[actor]);
	});

	const string KEVIN_BACON = "Bacon, Kevin";

	while (true) {
		// Demande du point de départ
		string start;
		cout << "Départ: ";
		getline(cin, start);

		// Arrêt du programme
		if (start.empty()) break;

		try {
			// Génération du chemin
			auto p = path(g, indices, KEVIN_BACON, start);
			cout << endl;

			// Affichage du chemin
			for (const int& idx : p) {
				cout << labels[idx] << endl;
			}

			// Cacul de la distance
			cout << endl << "DISTANCE = " << p.size() / 2 << endl;
		} catch (const char* err) {
			cout << err << endl;
		}

		cout << endl;
	}
}
