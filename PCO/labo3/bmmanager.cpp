#include <QString>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QMutexLocker>

#include "bmmanager.h"
#include "banditmanchot_interface.h"

#include <iostream>
#include <math.h>
#include <time.h>

// En milliseconds
#define TIMEOUT 10000

// Nombre de rouleau utilisé par la machine
#define NB_BARREL 3

class BarrelThread : public QThread
{
private:
    static int nextId;

    int id;
    int value;
    QMutex mutex;

    void nextValue() {
        setValue((value + 1) % 10);
    }

public:
    BarrelThread(): id(nextId++) {}

    void run() Q_DECL_OVERRIDE {
        for(;;){
            usleep(10000);
            nextValue();
        }
    }

    int getValue() {
        QMutexLocker lock(&mutex);
        return value;
    }

    void setValue(int v) {
        QMutexLocker lock(&mutex);
        value = v % 10;
        setValeurRouleau(id, value);
    }

    void shuffle() {
        setValue(rand() % 10);
    }
};

int BarrelThread::nextId = 0;
bool isRunning = false;

BarrelThread barrels[NB_BARREL];
QTimer timer;

int nextBarrelToStop = 0;
size_t jackpot = 0;

QMutex stopMutex;

void BmManager::start()
{
    srand(time(NULL));

    for(int i = 0; i < NB_BARREL; i++) {
        barrels[i].shuffle();
    }

    setMessage("Bienvenue, insérez une pièce pour commencer");
    timer.stop();

    connect(&timer, SIGNAL(timeout()), this, SLOT(AbortGame()));
}

void BmManager::end()
{
    for(int i = 0; i < NB_BARREL; i++)
        barrels[i].terminate();
}

void BmManager::pieceIntroduite()
{
    if(!isRunning) {
        setJackpot(++jackpot);
        isRunning = true;
        startBarrels();
        setMessage("Partie lancée");
        timer.start(TIMEOUT);
        for(int i = 0; i < NB_BARREL; i++) {
            barrels[i].shuffle();
        }
    }
}

void BmManager::boutonStop()
{
    QMutexLocker lock(&stopMutex);
    if(isRunning) {
        if(nextBarrelToStop < NB_BARREL) {
            barrels[nextBarrelToStop++].terminate();
            timer.start(TIMEOUT);
        }
        if(nextBarrelToStop == NB_BARREL) {
            if (barrels[0].getValue() == barrels[1].getValue() && barrels[1].getValue() == barrels[2].getValue()) {
                int gain = round((double)jackpot / 2);
                jackpot -= gain;
                setJackpot(jackpot);
                setMessage("Vous avez gagné " + QString::number(gain) + " !!");
            }
            else if(barrels[0].getValue() == barrels[1].getValue() || barrels[1].getValue() == barrels[2].getValue() || barrels[0].getValue() == barrels[2].getValue() ) {
                int gain = round((double)jackpot / 4);
                jackpot -= gain;
                setJackpot(jackpot);
                setMessage("Vous avez gagné " + QString::number(gain) + " !");
            }
            else {
                setMessage("Dommage...");
            }

            nextBarrelToStop = 0;
            isRunning = false;
        }
    }
}

void BmManager::startBarrels() {
    for(int i = 0; i < NB_BARREL; i++)
        barrels[i].start();
}

void BmManager::AbortGame() {
    // Bloc pour éviter un dead lock par l'appel de boutonStop qui va
    // également créer un QMutexLocker sur stopMutex.
    {
        QMutexLocker lock(&stopMutex);
        timer.stop();
        for(; nextBarrelToStop < NB_BARREL; nextBarrelToStop++)
            barrels[nextBarrelToStop].terminate();
    }
    boutonStop();
}

