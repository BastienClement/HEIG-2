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

class ParallelPrime {
private:
    class PrimeThread : public QThread {
    private:
        uint64_t n, lower, upper;
        ParallelPrime* pp;

        void run() {
            for (uint64_t i = lower; i < upper; i++) {
                if (n % i == 0) {
                    pp->notAPrimeNumber(this);
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
    QMutex mutex;

public:
    ParallelPrime(uint64_t n,  uint64_t sqrtn) {
        this->n = n;
        this->sqrtn = sqrtn;
    }

    void run(int count) {
        uint64_t slice = ((sqrtn - 2) / count) + 1;
        uint64_t base = 2;
        isPrime = true;

        for (int t = 0; t < count && base <= sqrtn; t++, base += slice) {
            threads.append(new PrimeThread(n, base, min(sqrtn, base + slice), this));
        }

        for (PrimeThread* pt : threads) pt->start();
        for (PrimeThread* pt : threads) pt->wait();

        for (PrimeThread* pt : threads) delete pt;

        threads.clear();
        cout << (isPrime ? "Prime number!" : "NOT a prime number!") << endl;
    }

    void notAPrimeNumber(PrimeThread* child) {
        if (mutex.tryLock()) {
            isPrime = false;
            for (PrimeThread* pt : threads) {
                if (pt != child)
                    pt->terminate();
            }
            mutex.unlock();
        }
    }
};



int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Not enought arguments !" << endl;
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
