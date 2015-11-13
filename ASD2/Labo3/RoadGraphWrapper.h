//
// Created by Bastien Clément on 05.11.15.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H

#include "RoadNetwork.h"
#include <functional>

/**
 * Wrapper d'un RoadNetwork en graphe non orienté
 */
class RoadGraphWrapper {
private:
	typedef std::function<double(RoadNetwork::Road)> Weighting;

	/**
	 * Le road network à interroger
	 */
	const RoadNetwork& rn;

	/**
	 * Une fonction attribuant à chaque route un poids
	 */
	Weighting weighting;

public:
	/**
	 * Constructeur
	 */
	RoadGraphWrapper(const RoadNetwork& rn, Weighting w): rn(rn), weighting(w) {}

	/**
	 * Nombre de sommets dans le graphe.
	 * Dans notre cas, il s'agit du nombre de ville.
	 */
	int V() const {
		return rn.cities.size();
	}

	/**
	 * Définition du type d'arête à utiliser
	 */
	typedef WeightedEdge<double> Edge;

	/**
	 * Invoque une fonction f pour chaque arête du graphe.
	 * Dans notre cas, chaque route.
	 */
	template<typename Func>
	void forEachEdge(Func f) const {
		for (const auto road : rn.roads) {
			f(Edge(road.cities.first, road.cities.second, weighting(road)));
		}
	}
};

// ----

/**
 * Wrapper d'un RoadNetwork en graphe orienté
 */
class RoadDiGraphWrapper {
private:
	typedef std::function<double(RoadNetwork::Road)> Weighting;

	/**
	 * Le road network à interroger
	 */
	const RoadNetwork& rn;

	/**
	 * Une fonction attribuant à chaque route un poids
	 */
	Weighting weighting;

public:
	/**
	 * Constructeur
	 */
	RoadDiGraphWrapper(const RoadNetwork& rn, Weighting w): rn(rn), weighting(w) {}

	/**
	 * Définition du type des arêtes de ce graphe.
	 */
	typedef WeightedDirectedEdge<double> Edge;

	/**
	 * Nombre de sommets dans le graphe.
	 * Dans notre cas, il s'agit du nombre de ville.
	 */
	int V() const {
		return rn.cities.size();
	}

	/**
	 * Invoque une fonction f pour chaque arête liées à un sommet.
	 * Dans notre cas, les routes sont toutes bi-directionnelles, on vérifie
	 * donc l'égalité avec les deux extêmités des routes.
	 */
	template<typename Func>
	void forEachAdjacentEdge(int v, Func f) const {
		for (const auto road : rn.roads) {
			if (road.cities.first == v) {
				f(Edge(road.cities.first, road.cities.second, weighting(road)));
			} else if (road.cities.second == v) {
				f(Edge(road.cities.second, road.cities.first, weighting(road)));
			}
		}
	}
};

#endif //LABO3_ROADGRAPHWRAPPER_H
