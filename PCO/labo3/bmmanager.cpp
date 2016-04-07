#include <QString>
#include <QThread>
#include <QTimer>


#include "bmmanager.h"
#include "banditmanchot_interface.h"


#include <iostream>
#include <math.h>
#include <time.h>

// En microsecondes
#define DelaiLocal 4000000

// Nombre de rouleau utilisé par la machine
#define NB_BARREL 3

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

RouleauThread myThreads[NB_BARREL];
QTimer timer;

int nextThreadToStop = 0;
size_t jackpot = 0;

void BmManager::start()
{
    //Intitialisation de rouleaeux
    srand(time(NULL));
    for(int i = 0; i < NB_BARREL; i++) {
        int randomVal = rand() % 10;
        setValeurRouleau(i, randomVal);
        myThreads[i].setValue(randomVal);
    }

    setMessage("Bienvenue, insérez une pièce pour commencer");

    /*
     * Connexion de la méthode timeout() du timer et de la méthode
     * abortGame(), afin que lorsque le timer arrive à 0, il soit possible
     * de stoper tout les rouleaux.
     */
    connect(&timer, SIGNAL(timeout()), this, SLOT(abortGame()));
}

void BmManager::end()
{
    for(int i = 0; i < NB_BARREL; i++)
        myThreads[i].terminate();
}

void BmManager::pieceIntroduite()
{
    /*
     * Si la machine n'est pas encore lancé, démarre l'application avec
     * un délai avant le quelle la machine s'arrête si l'utilisateur
     * n'as pas appuyé sur le bouton stop.
     */
    if(!isRunning) {
        setJackpot(++jackpot);
        isRunning = true;
        startBarrel();
        setMessage("Partie lancée");
        timer.start(DelaiLocal);
        /*
         * Attribution de nouvelle valeur aléatoire aux rouleaux afin
         * de modifier les résultats de la partie précédente.
         */
        for(int i = 0; i < NB_BARREL; i++) {
            myThreads[i].setValue(rand() % 10);
        }
    }
}

void BmManager::boutonStop()
{
    if(isRunning) {
        /*
         * Arrête le prochain rouleau s'il y en a toujours entrain de tourner.
         * Le délai local est réinitialisé à chaque arrêt de rouleau.
         */
        if(nextThreadToStop < NB_BARREL) {
            myThreads[nextThreadToStop++].terminate();
            timer.start(DelaiLocal);
        }

        /*
         * Si tous les rouleaux ont été arrétés, alors on contrôle si il n'y a pas gain,
         * et on récompense le joueur en conséquence.
         */
        if(nextThreadToStop == NB_BARREL) {
            timer.stop();
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
    for(int i = 0; i < NB_BARREL; i++)
        myThreads[i].start();
}

void BmManager::abortGame() {
    timer.stop();

    /*
     * Arrêt de tout les rouleaux d'un seul coup.
     */
    for(; nextThreadToStop < NB_BARREL; nextThreadToStop++)
        myThreads[nextThreadToStop].terminate();
    /*
     * Même si tous les rouleaux sont déjà arrêté, la méthode boutonStop()
     * est appelé, afin de profité de la partie contrôle de victoire de la
     * méthode.
     */
    boutonStop();
}

