/******************************************************************************
  \file main.cpp
  \author Yann Thoma
  \date 05.05.2011

  Ce fichier propose un squelette pour l'application de gestion des vélos.
  Il est évident qu'il doit être grandement modifié pour respecter la donnée,
  mais vous y trouvez des exemples d'appels de fonctions de l'interface.
  ****************************************************************************/

/**
  Architecture générale
  =====================

  Nous avons tenté de rester le plus simple possible et réutiliser la classe
  Habitant qui était fournie. Par simplicité, nous n'avons pas de classe particulière
  pour le dépot ou le van, et traitons ces entités en tant que Site ou Habitant.

  Chaque site est une entité indépendante dotée des mécanismes de synchronisation
  nécessaire à la réalistaion des objectifs du laboratoire. Nous n'avons pas eu
  besoin de mutex global entre tous les sites, ce qui permet une concurrence maximale
  (il n'est pas nécessaire de vérouiller tous les sites lorsque le vélo est déposé
  sur un site unique)

  La classe Site fourni également une méthode `.atomically(fn)` prenant une fonction
  en paramètre qui sera appelée avec le site manipulé. Le verrou du site sera
  automatiquement acquis avant l'exécution de la fonction puis libéré une fois la
  fonction terminée. Ceci permet d'implémenter facilement les méthodes du van sans
  se soucier d'éventuelles préemptions entre le moment où les vélos présents sur un
  site sont compté puis retirés. En effet, l'opération dans son ensemble est implémentée
  dans la fonction passée en paramètre et s'effectue donc sans relacher le verrou,
  de façon atomique.
  */

#include <QApplication>
#include <QWaitCondition>
#include <QMutexLocker>
#include <QVector>
#include <QThread>
#include <algorithm>
#include <string>
#include <iostream>
#include "bikinginterface.h"

using namespace std;
using uint = unsigned int;

/**
 Inteface pour l'envoi de commandes à l'interface graphique.
 Elle peut sans problème être partagée entre les différents threads.
 */
BikingInterface *gui_interface;

/**
 * Un site de la ville avec des bornes pour vélo.
 *
 * Chaque site possède un nombre de bornes et un compteur de vélos
 * actuellement présents sur le site. Il fourni des méthodes pour
 * prendre et poser un vélo de façon thread-safe.
 *
 * Le dépot est considéré comme un site avec un nombre important
 * de bornes disponibles.
 *
 * Les méthodes de cette classe prennent un paramètre `lock`
 * optionnel qui va indiquer qu'il est nécessaire de vérouiller
 * le mutex lors de la manipulation des variables. Ceci afin de
 * permettre l'utilisation de l'objet dans la méthode `atomically`
 * sans provoquer de dead-lock.
 */
class Site {
private:
    /** ID du site */
    uint _id;

    /** Nombre de vélos sur le site */
    uint _bikes;

    /** Nombre de bornes sur le site */
    uint _spots;

    /** Mutex de protection pour les variables privées */
    QMutex _mutex;

    /** Un nouveau vélo est disponible */
    QWaitCondition _bikeAvailable;

    /** Une nouvelle borne est disponible */
    QWaitCondition _spotAvailable;

public:
    Site(uint id, uint spots, uint bikes) : _id(id), _bikes(bikes), _spots(spots) {
        gui_interface->setInitBikes(_id, _bikes);
    }

    /** Retourne le nombre de vélos disponibles */
    uint bikes(bool lock = false) {
        if (lock) _mutex.lock();
        return _bikes;
        if (lock) _mutex.unlock();
    }

    /** Retourne le nombre de bornes disponibles */
    uint spots(bool lock = false) {
        if (lock) _mutex.lock();
        return _spots;
        if (lock) _mutex.unlock();
    }

    /**
     * Retire un vélo de ce site
     *
     * Si aucun vélo n'est disponibles, la méthode bloque
     * jusqu'à ce qu'un vélo le soit.
     */
    void take(bool lock = false) {
        if (lock) _mutex.lock();
        while (_bikes < 1) _bikeAvailable.wait(&_mutex);
        _bikes -= 1;
        _spotAvailable.wakeOne();
        gui_interface->setBikes(_id, _bikes);
        if (lock) _mutex.unlock();
    }

    /**
     * Tente de retirer un vélo de ce site de façon non-bloquante.
     *
     * Si au moins un vélo est présent, ce vélo est retiré
     * et la méthode retourne true, dans le cas contraire,
     * la méthode retourne false.
     */
    bool tryTake(bool lock = false) {
        if (lock) _mutex.lock();
        bool ret = false;
        if (_bikes >= 1) {
            take();
            ret = true;
        }
        if (lock) _mutex.unlock();
        return ret;
    }

    /**
     * Ajoute un vélo sur ce site.
     *
     * Si aucune borne n'est disponible, la méthode bloque jusqu'à
     * ce qu'une borne soit libérée.
     */
    void put(bool lock = false) {
        if (lock) _mutex.lock();
        while (_bikes == _spots) _spotAvailable.wait(&_mutex);
        _bikes += 1;
        _bikeAvailable.wakeOne();
        gui_interface->setBikes(_id, _bikes);
        if (lock) _mutex.unlock();
    }

    /**
     * Exécute un traitement de façon atomique sur le site.
     *
     * La méthode passée en paramètre reçoit un pointeur vers le
     * site manipulé et le verou du site est gardé pendant toute
     * la durée d'exécution.
     *
     * Pour éviter un dead-lock, il est important que la méthode
     * passée en paramètre ne tente pas d'obtenir à nouveau le
     * verrou sur ce site.
     */
    template<typename Fn>
    void atomically(Fn fn) {
        _mutex.lock();
        fn(this);
        _mutex.unlock();
    }
};

/**
 * Un habitant de la ville, qui utilise des vélos.
 *
 * L'habitant ID 0 est considéré comme le van.
 */
class Habitant: public QThread
{
private:
    /** ID de l'habitant */
    uint id;

    /** Liste des sites à disposition */
    QVector<Site*>* sites;

    /** Site actuel */
    uint curSite;

public:
    Habitant(uint id, uint loc, QVector<Site*>* sites) : id(id), sites(sites), curSite(loc) {
        if (id == 0) {
            gui_interface->vanTravel(curSite, curSite, 10);
        } else {
            gui_interface->setInitPerson(curSite, id);
        }
    }

    void run() Q_DECL_OVERRIDE {
        /** Nombre de sites disponibles */
        uint nbSites = sites->size();

        /** Nombre de vélo chargés dans le van */
        uint load = 0;

        /** Initialisation de l'aléatoire */
        //qsrand(id);

        forever {
            // Affichage d'un message
            gui_interface->consoleAppendText(id , "Salut");

            // Temps de l'action
            uint time = (rand() % 1000) + 1000;

            if (id == 0) { // Van
                if (curSite == nbSites - 1) {
                    // Si le van est au dépot, on commence par décharger
                    // tous les vélos chargés ...
                    sites->at(curSite)->atomically([&](Site* site) {
                        for (uint i = 0; i < load; i++) {
                            site->put();
                        }
                        load = 0;
                    });

                    // Puis on fait un pause...
                    QThread::usleep(3000 * 1000);

                    // Puis on charge le nombre de vélos nécessaires
                    sites->at(curSite)->atomically([&](Site* site) {
                        load = min((uint) 2, site->bikes());
                        for (uint i = 0; i < load; i++) {
                            site->take();
                        }
                    });
                } else {
                    // Si le van n'est pas au dépot on tente d'équilibrer le nombre
                    // de vélos sur le site
                    sites->at(curSite)->atomically([&](Site* site) {
                        if (site->bikes() > site->spots() - 2) {
                            uint c = min(site->bikes() - (site->spots() - 2), 4 - load);
                            load += c;
                            for (uint i = 0; i < c; i++) {
                                site->take();
                            }
                        } else {
                            uint c = min((site->spots() - 2) - site->bikes(), load);
                            load -= c;
                            for (uint i = 0; i < c; i++) {
                                site->put();
                            }
                        }
                    });
                }

                // On voyage jusqu'au prochain site
                int nextSite = (curSite + 1) % (nbSites);
                gui_interface->vanTravel(curSite, nextSite, time / 1.5);
                curSite = nextSite;
            } else { // Habitant
                // L'habitant prend un vélo
                sites->at(curSite)->take(true);

                // Il choisi une destination qui n'est pas le site actuel,
                // ni le dépot.
                uint destination;
                do {
                   destination = qrand() % (nbSites - 1);
                } while (destination == curSite);

                // Il effectue le trajet
                gui_interface->travel(id,            // ID de la personne
                                      curSite,       // Site de départ
                                      destination,   // site d'arrivée
                                      time);         // Temps en millisecondes

                curSite = destination;

                // Il dépose sont vélo
                sites->at(curSite)->put(true);

                // Puis effectue une activité
                QThread::usleep(time * 1000);
            }
        }
    }
};

/**
 * Thread de gestion de la console.
 *
 * Boucle infine qui lis la console caractère par caractère.
 * Un 'p' ajoute un vélo dans le dépot
 * Un 't' retire un vélo libre sur l'un des site, ou affiche
 * un message d'erreur si aucun vélo n'est disponible.
 */
class ConsoleThread : public QThread {
private:
    QVector<Site*>* sites;

public:
    ConsoleThread(QVector<Site*>* sites) : sites(sites) {}

    void run() Q_DECL_OVERRIDE {
        forever {
            char cmd;
            cin >> cmd;
            switch (cmd) {
                case 'p':
                    sites->at(sites->size() - 1)->put(true);
                    cout << "Vélo ajouté dans le dépot." << endl;
                break;

                case 't':
                    for (int i = 0; i < sites->size(); i++) {
                        if (sites->at(i)->tryTake(true)) {
                            cout << "Vélo retiré." << endl;
                            goto success;
                        }
                    }
                    cout << "Aucun vélo trouvé." << endl;
                success:
                break;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc < 5) {
        return 1;
    }

    QApplication a(argc, argv);

    uint nbSites = stoi(argv[1]);
    if (nbSites < 2) {
        cerr << "Le nombre de site doit être >= 2" << endl;
        return 1;
    }

    uint nbHabitants = stoi(argv[2]);

    uint nbSpots = stoi(argv[3]);
    if (nbSpots < 4) {
        cerr << "Le nombre de bornes par site doit être >= 4" << endl;
        return 1;
    }

    uint nbVelo = stoi(argv[4]);
    if (nbVelo < nbSites * (nbSpots - 2) + 3) {
        cerr << "Le nombre de vélo est invalide." << endl;
        return 1;
    }

    // Initialisation de la partie graphique de l'application
    BikingInterface::initialize(nbHabitants,nbSites);
    // Création de l'interface pour les commandes à la partie graphique
    gui_interface=new BikingInterface();

    QVector<Site*> sites;

    // Création sites
    for (uint i = 0; i <= nbSites; i++) {
        if (i < nbSites) {
            sites.push_back(new Site(i, nbSpots, nbSpots - 2));
        } else {
            sites.push_back(new Site(i, nbVelo, nbVelo - (nbSpots - 2) * nbSites));
        }
    }

    // Création de threads
    Habitant* threads[nbHabitants];
    for(uint t = 0, i = 0; t < nbHabitants; t++, i++){
        cout << "Création du thread "<< t << endl;
        threads[t] = new Habitant(t, (t == 0) ? nbSites : 0, &sites);
        threads[t]->start();
    }

    // Thread console
    ConsoleThread console(&sites);
    console.start();

    // Attention, il est obligatoire d'exécuter l'instruction suivante.
    // C'est elle qui permet la gestion de la boucle des évévements de
    // l'application graphique.
    return a.exec();
}


