/*
 * File:   ShortestPath.h
 * Author: Olivier Cuisenaire
 *
 * Created on 5. novembre 2014, 10:16
 */

#ifndef ASD2_ShortestPath_h
#define ASD2_ShortestPath_h

#include <algorithm>
#include <queue>
#include <vector>
#include <set>
#include <functional>

// Classe parente de toutes les classes de plus court chemin.
// Defini les membres edgeTo et distanceTo commun à toutes ces
// classes, ainsi que les methodes DistanceTo, EdgeTo et PathTo
// qui permettent de les interroger.
//
// Le calcul des plus courts chemins est fait dans les constructeurs
// des classes derivees.

template<typename GraphType>
// Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// EdgeWeightedDiGraph et definir le
// type GraphType::Edge
class ShortestPath {
public:
	// Type des arcs. Normalement ASD2::DirectedEdge<double>
	typedef typename GraphType::Edge Edge;

	// Type des poids. Normalement double ou int.
	typedef typename Edge::WeightType Weight;

	// Listes d'arcs et de poids
	typedef std::vector<Edge> Edges;
	typedef std::vector<Weight> Weights;

	// Renvoie la distance du chemin le plus court du sommet source a v
	Weight DistanceTo(int v) {
		return distanceTo.at(v);
	}

	// Renvoie le dernier arc u->v du chemin le plus court du sommet source a v
	Edge EdgeTo(int v) {
		return edgeTo.at(v);
	}

	// Renvoie la liste ordonnee des arcs constituant un chemin le plus court du
	// sommet source à v.
	Edges PathTo(int v) {
		Edges edges;
		while (DistanceTo(v) > 0) {
			Edge e = EdgeTo(v);
			edges.push_back(e);
			v = e.From();
		}
		reverse(edges.begin(), edges.end());
		return edges;
	}

protected:
	Edges edgeTo;
	Weights distanceTo;
};

// Classe a mettre en oeuvre au labo 3. S'inspirer de BellmaFordSP pour l'API

template<typename GraphType>
class DijkstraSP : public ShortestPath<GraphType> {
public:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;

	typedef std::pair<Weight, int> WeightedVertex;

	DijkstraSP(const GraphType& g, int v) {
		const int V = g.V();

		this->edgeTo.resize(V);
		this->distanceTo.resize(V);

		std::set<WeightedVertex> pq;
		std::vector<bool> marked(V, false);

		for (int i = 0; i < V; i++) {
			this->distanceTo.at(i) = std::numeric_limits<Weight>::infinity();
		}

		this->distanceTo.at(v) = 0;
		pq.insert(std::make_pair(0, v));

		while (!pq.empty()) {
			int v = pq.begin()->second;
			pq.erase(pq.begin());

			marked.at(v) = true;

			g.forEachAdjacentEdge(v, [&](Edge edge) {
				// Sommet de destination
				int w = edge.To();
				if (marked.at(w)) return;

				// Distance de la destination
				Weight old_weight = this->distanceTo.at(w);
				Weight new_weight = this->distanceTo.at(v) + edge.Weight();

				if (new_weight < old_weight) {
					pq.erase(std::make_pair(old_weight, w));
					pq.insert(std::make_pair(new_weight, w));
					this->edgeTo.at(w) = edge;
					this->distanceTo.at(w) = new_weight;
				}
			});
		}
	}
};

// Algorithme de BellmanFord.

template<typename GraphType> // Type du graphe pondere oriente a traiter
// GraphType doit se comporter comme un
// EdgeWeightedDiGraph et definir forEachEdge(Func),
// ainsi que le type GraphType::Edge. Ce dernier doit
// se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
// To() et Weight()

class BellmanFordSP : public ShortestPath<GraphType> {

private:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;

	// Relachement de l'arc e
	void relax(const Edge& e) {
		int v = e.From(), w = e.To();
		Weight distThruE = this->distanceTo[v] + e.Weight();

		if (this->distanceTo[w] > distThruE) {
			this->distanceTo[w] = distThruE;
			this->edgeTo[w] = e;
		}
	}

public:

	// Constructeur a partir du graphe g et du sommet v a la source
	// des plus courts chemins
	BellmanFordSP(const GraphType& g, int v) {

		this->edgeTo.reserve(g.V());
		this->distanceTo.assign(g.V(), std::numeric_limits<Weight>::max());

		this->edgeTo[v] = Edge(v, v, 0);
		this->distanceTo[v] = 0;

		for (int i = 0; i < g.V(); ++i)
			g.forEachEdge([this](const Edge& e) {
				this->relax(e);
			});
	}
};


/* Fera l'objet d'un exercice de programmation
// Algorithme de BellmanFord avec queue simple reprenant les sommets ayant
// ete modifies par la derniere iteration.
template<typename GraphType> // Type du graphe pondere oriente a traiter
							 // GraphType doit se comporter comme un
							 // EdgeWeightedDiGraph et definir forEachAdjacentEdge(int,Func),
							 // ainsi que le type GraphType::Edge. Ce dernier doit
							 // se comporter comme ASD2::DirectedEdge, c-a-dire definir From(),
							 // To() et Weight()

class BellmanFordQueueSP : public ShortestPath<GraphType> {

private:
	typedef ShortestPath<GraphType> BASE;
	typedef typename BASE::Edge Edge;
	typedef typename BASE::Weight Weight;

public:
	BellmanFordQueueSP(const GraphType& g, int v) {

	}
};
*/

#endif
