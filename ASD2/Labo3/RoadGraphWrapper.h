//
// Created by Bastien Clément on 05.11.15.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H

#include "RoadNetwork.h"

struct ShortestWeighting {
	double operator() (RoadNetwork::Road edge) {
		return 0;
	}
};

struct FastestWeighting {
	double operator() (RoadNetwork::Road edge) {
		return 0;
	}
};

struct CheapestWeighting {
	double operator() (RoadNetwork::Road edge) {
		return 0;
	}
};

template <typename Weighting>
class RoadGraphWrapper : public EdgeWeightedGraph<double> {
private:
	typedef EdgeWeightedGraph<double> BASE;
	Weighting weighting;

public:
	RoadGraphWrapper(const RoadNetwork& rn): BASE(rn.cities.size()) {
		int E = rn.roads.size();
		for (int i = 0; i < E; i++) {
			auto road = rn.roads.at(i);
			auto cities = road.cities;
			addEdge(cities.first, cities.second, weighting(road));
		}
	}
};

template <typename Weighting>
class RoadDiGraphWrapper : public EdgeWeightedDiGraph<double> {
private:
	typedef EdgeWeightedDiGraph<double> BASE;
	Weighting weighting;

public:
	RoadDiGraphWrapper(const RoadNetwork& rn): BASE(rn.cities.size()) {
		int E = rn.roads.size();
		for (int i = 0; i < E; i++) {
			auto road = rn.roads.at(i);
			auto cities = road.cities;
			addEdge(cities.first, cities.second, weighting(road));
			addEdge(cities.second, cities.first, weighting(road));
		}
	}
};

#endif //LABO3_ROADGRAPHWRAPPER_H
