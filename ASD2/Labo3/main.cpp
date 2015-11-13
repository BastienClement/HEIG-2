/*
 * File:   main.cpp
 * ASD 2 - Labo 3
 * Author: Olivier Cuisenaire
 *
 * Created on 18. novembre 2014, 14:58
 */

#include <stdlib.h>
#include <iostream>
#include <ctime>

#include "RoadNetwork.h"
#include "MinimumSpanningTree.h"
#include "ShortestPath.h"

#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDiGraph.h"

#include "RoadGraphWrapper.h"

using namespace std;

// Calcule et affiche le plus court chemin de la ville depart a la ville arrivee
// en passant par le reseau routier rn. Le critere a optimiser est la distance.

void PlusCourtChemin(const string& depart, const string& arrivee, RoadNetwork& rn) {
    RoadDiGraphWrapper rgw(rn, [&](RoadNetwork::Road road) { return road.lenght; });
    DijkstraSP<RoadDiGraphWrapper> sp(rgw, rn.cityIdx.at(depart));

    double sum = 0;
    cout << depart << endl;

    auto path = sp.PathTo(rn.cityIdx.at(arrivee));
    for (auto road : path) {
        double length = road.Weight();
        sum += length;
        cout << rn.cities.at(road.To()).name << " [" << length << "]" << endl;
    }

    cout << "\n==> " << sum << " km" << endl << endl;
}

// Calcule et affiche le plus rapide chemin de la ville depart a la ville arrivee via la ville "via"
// en passant par le reseau routier rn. Le critere a optimiser est le temps de parcours
// sachant que l'on roule a 120km/h sur autoroute et 70km/h sur route normale.

void PlusRapideChemin(const string& depart, const string& arrivee, const string& via, RoadNetwork& rn) {
    RoadDiGraphWrapper rgw(rn, [&](RoadNetwork::Road road) {
        double motorway = road.motorway.Value();
        double hours = (motorway / 120 + (1 - motorway) / 70) * road.lenght;
        return hours * 60;
    });

    DijkstraSP<RoadDiGraphWrapper> sp(rgw, rn.cityIdx.at(via));

    auto path_depart = sp.PathTo(rn.cityIdx.at(depart));
    auto path_arrivee = sp.PathTo(rn.cityIdx.at(arrivee));

    reverse(path_depart.begin(), path_depart.end());

    double sum = 0;
    cout << depart << endl;

    for (auto road : path_depart) {
        double duration = road.Weight();
        sum += duration;
        cout << rn.cities.at(road.From()).name << " [" << duration << "]" << endl;
    }

    for (auto road : path_arrivee) {
        double duration = road.Weight();
        sum += duration;
        cout << rn.cities.at(road.To()).name << " [" << duration << "] " << endl;
    }

    cout << "\n==> " << sum << " minutes" << endl << endl;
}

// Calcule et affiche le plus reseau a renover couvrant toutes les villes le moins
// cher, en sachant que renover 1km d'autoroute coute 15 MF, et renover 1km de route normale
// coute 7 MF.

void ReseauLeMoinsCher(RoadNetwork &rn) {
    RoadGraphWrapper rgw(rn, [&](RoadNetwork::Road road) {
        double motorway = road.motorway.Value();
        double avg_unit_cost = motorway * 15 + (1 - motorway) * 7;
        return avg_unit_cost * road.lenght;
    });

    auto mst = MinimumSpanningTree<RoadGraphWrapper>::Kruskal(rgw);
    double sum = 0;

    for (const auto edge: mst) {
        int from_idx = edge.Either();
        int to_idx = edge.Other(from_idx);

        string from = rn.cities.at(from_idx).name;
        string to = rn.cities.at(to_idx).name;

        double cost = edge.Weight();
        sum += cost;

        cout << from << " <=> " << to << " [" << cost << "]" << endl;
    }

    cout << "\n==> " << sum << " MF" << endl << endl;
}

// compare les algorithmes Dijkstra et BellmanFord pour calculer les plus courts chemins au
// sommet 0 dans le graphe defini par filename.
// a utiliser pour tester votre implementation de Dijkstra

void testShortestPath(string filename)
{
    cout << "Testing " << filename << endl;

    bool ok = true;

    typedef EdgeWeightedDiGraph<double> Graph;
    Graph ewd(filename);

    clock_t startTime = clock();

    BellmanFordSP<Graph> referenceSP(ewd,0);

    cout << "Bellman-Ford: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    startTime = clock();

    DijkstraSP<Graph> testSP(ewd,0);

    cout << "Dijkstra:     " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    for (int v=0; v<ewd.V(); ++v) {
        if (referenceSP.DistanceTo(v) != testSP.DistanceTo(v) ) {
            cout << "Oops: vertex " << v << " has " << referenceSP.DistanceTo(v) << " != " <<  testSP.DistanceTo(v) << endl;
            ok = false;
            break;
        }
    }

    if(ok) cout << " ... test succeeded " << endl << endl;
}

int main(int argc, const char * argv[]) {

    testShortestPath("tinyEWD.txt");
    testShortestPath("mediumEWD.txt");
    testShortestPath("1000EWD.txt");
    //testShortestPath("10000EWD.txt");
    //testShortestPath("largeEWD.txt"); // disponible sur le moodle du cours

    RoadNetwork rn("reseau.txt");

    cout << "1. Chemin le plus court entre Geneve et Emmen" << endl;

    PlusCourtChemin("Geneve", "Emmen", rn);

    cout << "2. Chemin le plus court entre Lausanne et Bale" << endl;

    PlusCourtChemin("Lausanne", "Basel", rn);

    cout << "3. chemin le plus rapide entre Geneve et Emmen en passant par Yverdon" << endl;

    PlusRapideChemin("Geneve", "Emmen", "Yverdon-Les-Bains", rn);

    cout << "4. chemin le plus rapide entre Geneve et Emmen en passant par Vevey" << endl;

    PlusRapideChemin("Geneve", "Emmen", "Vevey", rn);

    cout << "5. Quelles routes doivent etre renovees ? Quel sera le cout de la renovation de ces routes ?" << endl;

    ReseauLeMoinsCher(rn);

    return EXIT_SUCCESS;
}
