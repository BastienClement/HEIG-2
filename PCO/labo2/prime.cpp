#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <iostream>
#include <cmath>
#include <cstdint>
#include <QThread>
#include <QVector>
#include <QTime>
#include <QMutex>
#include <QMutexLocker>

using namespace std;

// Various prime numbers:
// 433494437
// 2971215073
// 68720001023
// 4398050705407
// 70368760954879
// 18014398241046527
// 99194853094755497
// 981168724994134051

/**
 * Test si un nombre est premier en le divisant par tous les
 * nombres entre 2 et sqrtn.
 *
 * @param n      Le nombre à tester
 * @param sqrtn  La valeur maximale à tester
 */
void single(uint64_t n, uint64_t sqrtn) {
    bool prime = n % 2 == 1;

    if (prime) {
        for (uint64_t i = 3; i < sqrtn; i += 2) {
            if (n % i == 0) {
                prime = false;
                break;
            }
        }
    }

    cout << (prime ? "Prime number!" : "NOT a prime number!") << endl;
}

/**
 * Implémentation parallèle de l'algorithme précédent.
 * Cette classe se charge de créer les threads nécessaires au calcul
 * et de gérer l'arrêt lorsque le résultat a été déterminé.
 */
class ParallelPrime {
private:
    /**
     * Thread worker chargé d'effectuer une part du travail
     */
    class PrimeThread : public QThread {
    private:
        /**
         * Nombre à tester, borne inférieure, borne suppérieure
         */
        uint64_t n, lower, upper;

        /**
         * Pointeur vers l'objet ParallelPrime parent
         */
        ParallelPrime* pp;

        /**
         * Méthode principale du thread
         */
        void run() {
            Q_ASSERT(lower % 2 == 1);
            for (uint64_t i = lower; i < upper; i += 2) {
                if (n % i == 0) {
                    // Diviseur trouvé
                    pp->notAPrimeNumber(this);
                    return;
                }
            }
        }

    public:
        PrimeThread(uint64_t n, uint64_t l, uint64_t u, ParallelPrime* pp)
            : n(n), upper(u), pp(pp) {
            lower = (l % 2 == 0) ? l + 1 : l;
        }
    };

    /**
     * Nombre à tester, borne maximale
     */
    uint64_t n, sqrtn;

    /**
     * Liste des workers
     */
    QVector<PrimeThread*> threads;

    /**
     * Résultat final
     */
    bool isPrime;

    /**
     * Mutex utilisé pour s'assurer qu'il ne soit pas possible
     * de tuer des threads au mauvais moment.
     */
    QMutex mutex;

public:
    ParallelPrime(uint64_t n,  uint64_t sqrtn) : n(n), sqrtn(sqrtn) {}

    /**
     * Recherche un diviseur du nombre n et affiche le résultat final.
     * @param count Le nombre de threads à utiliser
     */
    void run(int count) {
        if (n % 2 == 0) {
            // Optimistaion dans le cas où le nombre est pair
            // Dans le cas contraire, on ne testera que des diviseurs impairs
            isPrime = false;
        } else {
            // Plage de travail d'un worker
            uint64_t slice = ((sqrtn - 3) / count) + 1;

            // Valeur de départ d'un worker
            uint64_t base = 3;

            // On suppose le nombre premier jusqu'à avoir trouvé un diviseur
            isPrime = true;

            // Création des threads worker avec leur plage de travail respective
            {
                // On vérouille le mutex le temps du lancement pour pas qu'il soit possible
                // de commencer à terminer les threads avant qu'ils soient tous lancés.
                QMutexLocker lock(&mutex);

                for (int t = 0; t < count && base <= sqrtn; t++, base += slice) {
                    PrimeThread* pt = new PrimeThread(n, base, min(sqrtn, base + slice), this);
                    threads.append(pt);
                    pt->start();
                }
            }

            // On attend que tous les threads se terminent
            for (PrimeThread* pt : threads) pt->wait();

            // Destruction des threads créés
            for (PrimeThread* pt : threads) delete pt;
            threads.clear();
        }

        cout << (isPrime ? "Prime number!" : "NOT a prime number!") << endl;
    }

    /**
     * Un des workers a trouvé un diviseur de n.
     * Le nombre n'est donc pas premier, et il est possible de tuer tous les workers.
     *
     * Cette méthode s'execute sur le thread d'un worker et peut potentiellement être
     * appelée plusieurs fois simultanément.
     *
     * Lorsque le thread worker trouve un diviseur, il appel cette méthode avec un
     * pointeur vers lui même, ce qui permet de ne pas le terminer de force.
     *
     * @param child Pointeur vers le worker qui a trouvé le diviseur
     */
    void notAPrimeNumber(PrimeThread* child) {
        QMutexLocker lock(&mutex);
        isPrime = false;
        for (PrimeThread* pt : threads) {
            if (pt != child)
                pt->terminate();
        }
    }
};


int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Not enought arguments!" << endl;
        return 1;
    }

    uint64_t n = stoull(argv[1]);
    uint64_t sqrtn = sqrt(n);

    // Correction des incertitudes double -> uint64 et divisions entières
    // La racine effective sera un peu plus grande que la racine réelle.
    while ((n / sqrtn) + 1 > sqrtn) sqrtn++;

    QTime t;

    t.start();
    single(n,sqrtn);
    cout << "Temps single : " << t.restart() << endl;

    ParallelPrime pp(n, sqrtn);
    pp.run(stoi(argv[2]));

    cout << "Temps threads : " << t.restart() << endl;

    return 0;
}
