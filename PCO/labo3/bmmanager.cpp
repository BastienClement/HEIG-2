#include <QString>
#include <QThread>
#include <QTimer>


#include "bmmanager.h"
#include "banditmanchot_interface.h"


#include <iostream>
#include <math.h>
#include <time.h>

// En microsecondes
#define DelaiLocal  4000000

class RouleauThread : public QThread
{
private:
    int rouleau;
    int id;
    static int compteur;
    int valeur;
public:
    RouleauThread(): id(compteur++){}
    void run() Q_DECL_OVERRIDE {
        setValeurRouleau(id,valeur);
        for(;;){
            usleep(10000);
            valeur = (valeur + 1) % 10;
            setValeurRouleau(id,valeur);
        }
    }

    int getValue() const { return valeur; }
    void setValue(int v) { valeur = v % 10;}
};

int RouleauThread::compteur = 0;
bool isRunning = false;

RouleauThread myThreads[3];
QTimer timer;

int nextThreadToStop = 0;
size_t jackpot = 0;

void BmManager::start()
{
    srand(time(NULL));
    for(int i = 0; i < 3; i++) {
        int randomVal = rand() % 10;
        setValeurRouleau(i, randomVal);
        myThreads[i].setValue(randomVal);
    }

    setMessage("Bienvenue, insérez une pièce pour commencer");
    timer.stop();

    connect(&timer, SIGNAL(timeout()), this, SLOT(AbortGame()));
}

void BmManager::end()
{
    for(int i = 0; i < 3; i++)
        myThreads[i].terminate();
}

void BmManager::pieceIntroduite()
{
    if(!isRunning) {
        setJackpot(++jackpot);
        isRunning = true;
        startBarrel();
        setMessage("Partie lancée");
        timer.start(DelaiLocal);
    }
}

void BmManager::boutonStop()
{
    if(isRunning) {
        if(nextThreadToStop < 3) {
            myThreads[nextThreadToStop++].terminate();
            timer.start(DelaiLocal);
        }
        if(nextThreadToStop == 3) {
            if (myThreads[0].getValue() == myThreads[1].getValue() && myThreads[1].getValue() == myThreads[2].getValue()) {
                int gain = round((double)jackpot / 2);
                jackpot -= gain;
                setJackpot(jackpot);
                setMessage("Vous avez gagné " + QString::number(gain) + " !!");
            }
            else if( myThreads[0].getValue() == myThreads[1].getValue() || myThreads[1].getValue() == myThreads[2].getValue() || myThreads[0].getValue() == myThreads[2].getValue() ) {
                int gain = round((double)jackpot / 4);
                jackpot -= gain;
                setJackpot(jackpot);
                setMessage("Vous avez gagné " + QString::number(gain) + " !");
            }
            else {
                setMessage("Dommage...");
            }

            nextThreadToStop = 0;
            isRunning = false;
        }
    }
}

void BmManager::startBarrel() {
    for(int i = 0; i < 3; i++)
        myThreads[i].start();
}

void BmManager::AbortGame() {
    for(; nextThreadToStop < 3; nextThreadToStop++)
        myThreads[nextThreadToStop].terminate();
    timer.stop();
    setMessage("Fin de partie. Il faut jouer plus rapidement.");
    nextThreadToStop = 0;
    isRunning = false;
}

