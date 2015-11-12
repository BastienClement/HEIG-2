//
// Created by Bastien Clément on 05.11.15.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H

#include "RoadNetwork.h"
#include <functional>

class RoadGraphWrapper {
private:
	typedef std::function<double(RoadNetwork::Road)> Weighting;
	const RoadNetwork& rn;
	Weighting weighting;

public:
	RoadGraphWrapper(const RoadNetwork& rn, Weighting w): rn(rn), weighting(w) {}

	int V() const {
		return rn.cities.size();
	}

	typedef WeightedEdge<double> Edge;

	template<typename Func>
	void forEachEdge(Func f) const {
		for (const auto road : rn.roads) {
			f(Edge(road.cities.first, road.cities.second, weighting(road)));
		}
	}
};

// ----

class RoadDiGraphWrapper {
private:
	typedef std::function<double(RoadNetwork::Road)> Weighting;
	const RoadNetwork& rn;
	const Weighting weighting;

public:
	RoadDiGraphWrapper(const RoadNetwork& rn, Weighting w): rn(rn), weighting(w) {}

	typedef WeightedDirectedEdge<double> Edge;

	int V() const {
		return rn.cities.size();
	}

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
