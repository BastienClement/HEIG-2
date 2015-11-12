//
// Created by Bastien Clément on 05.11.15.
//

#ifndef LABO3_ROADGRAPHWRAPPER_H
#define LABO3_ROADGRAPHWRAPPER_H

#include "RoadNetwork.h"
#include <functional>

struct ShortestWeighting {
	double operator() (RoadNetwork::Road edge) {
		return edge.lenght;
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
class RoadGraphWrapper {
private:
	const RoadNetwork& rn;
	Weighting weighting;

public:
	RoadGraphWrapper(const RoadNetwork& rn): rn(rn) {}
};

class RoadDiGraphWrapper {
private:
	typedef std::function<double(RoadNetwork::Road)> Weighting;
	const RoadNetwork& rn;
	const Weighting weighting;

public:
	RoadDiGraphWrapper(const RoadNetwork& rn, Weighting w): rn(rn), weighting(w) {}

	struct Edge {
		typedef double WeightType;
		int from, to;
		WeightType weight;

		Edge(): from(-1), to(-1), weight(std::numeric_limits<WeightType>::max()) {}
		Edge(int from, int to, WeightType weight): to(to), from(from), weight(weight) {}

		int To() { return to; }
		int From() { return from; }

		WeightType Weight() { return weight; }
	};

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
