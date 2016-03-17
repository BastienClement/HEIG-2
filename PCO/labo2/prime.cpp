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

using namespace std;

// Various prime numbers:
// 433494437
// 2971215073
// 68720001023
// 4398050705407
// 70368760954879
// 18014398241046527
// 99194853094755497

/**
 * Test si un nombre est premier en le divisant par tous les
 * nombres entre 2 et sqrtn.
 *
 * @param n      Le nombre à tester
 * @param sqrtn  La valeur maximale à tester
 */
void single(uint64_t n,  uint64_t sqrtn) {
    for (uint64_t i = 2; i < sqrtn; i++) {
        if (n % i == 0) {
            cout << "NOT a prime number!" << endl;
            return;
        }
    }

    cout << "Prime number!" << endl;
    return;
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
            for (uint64_t i = lower; i < upper; i++) {
                if (n % i == 0) {
                    pp->notAPrimeNumber();
                    return;
                } else if (isInterruptionRequested()) {
                    return;
                }
            }
        }

    public:
        PrimeThread(uint64_t n, uint64_t l, uint64_t u, ParallelPrime* p)
            : n(n), lower(l), upper(u), pp(p) {}
    };

    uint64_t n, sqrtn;
    QVector<PrimeThread*> threads;
    bool isPrime;

public:
    ParallelPrime(uint64_t n,  uint64_t sqrtn) {
        this->n = n;
        this->sqrtn = sqrtn;
    }

    void run(int count) {
        uint64_t slice = ((sqrtn - 2) / count) + 1;
        uint64_t base = 2;
        isPrime = true;

        for (int t = 0; t < count; t++, base += slice) {
            threads.append(new PrimeThread(n, base, base + slice, this));
        }

        for (PrimeThread* pt : threads) pt->start();
        for (PrimeThread* pt : threads) pt->wait();

        for (PrimeThread* pt : threads) delete pt;

        threads.clear();
        cout << (isPrime ? "Prime number!" : "NOT a prime number!") << endl;
    }

    void notAPrimeNumber() {
        isPrime = false;
        for (PrimeThread* pt : threads) {
            pt->requestInterruption();
        }
    }
};



int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "HEU !" << endl;
        return 1;
    }

    uint64_t n = stoull(argv[1]);
    uint64_t sqrtn = sqrt(n);

    // Correction des incertitudes double -> uint64 et divisions entières
    // La racine effective sera un peu plus grande que la racine réelle.
    while ((n / sqrtn) + 1 > sqrtn) sqrtn++;

    ParallelPrime pp(n, sqrtn);
    pp.run(8);

    return 0;
}
