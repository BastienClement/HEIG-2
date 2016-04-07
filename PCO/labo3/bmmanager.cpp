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

    /*
     * Renvoie de la valeur du rouleau.
     */
    int getValue() {
        QMutexLocker lock(&mutex);
        return value;
    }

    /*
     * Change la valeur du rouleau et l'affiche dans l'interface.
     */
    void setValue(int v) {
        QMutexLocker lock(&mutex);
        value = v % 10;
        setValeurRouleau(id, value);
    }

    /*
     * Attribut une valeur aléatoire comprise en 0 et 9 au rouleau.
     */
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
    //Intitialisation de rouleaeux
	
    srand(time(NULL));

    for(int i = 0; i < NB_BARREL; i++) {
        barrels[i].shuffle();
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
        barrels[i].terminate();
}

/*
 * Fonction appelé lors de l'appui sur le bouton "Piece".
 * Si les rouleaux sont déjà entrain de tourner, la fonction ne fait rien.
 * Sinon, le jackpot est incrémenté et les rouleaux commencent à tourner.
 */
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
        startBarrels();
        setMessage("Partie lancée.");

        /*
         * Attribution de nouvelle valeur aléatoire aux rouleaux afin
         * de modifier les résultats de la partie précédente.
         */
        for(int i = 0; i < NB_BARREL; i++) {
            barrels[i].shuffle();
        }
		timer.start(TIMEOUT);
    }
}

/*
 * Fonction appelé lors de l'appui sur le bouton "Stop".
 * Si les rouleaux ne tournent pas la fonction ne fait rien.
 * Sinon, tant que tous les rouleaux ne sont pas arrêtés, la
 * fonction arrête un rouleau à chaque appel, jusqu'à ce qu'il soit
 * tous à l'arrêt.
 * Une fois que le dernier rouleau a été arrêté, la fonction contrôle si
 * les rouleaux n
 */
void BmManager::boutonStop()
{
    QMutexLocker lock(&stopMutex);
    if(isRunning) {
        /*
         * Arrête le prochain rouleau s'il y en a toujours entrain de tourner.
         * Le délai local est réinitialisé à chaque arrêt de rouleau.
         */
        if(nextBarrelToStop < NB_BARREL) {
            barrels[nextBarrelToStop++].terminate();
            timer.start(TIMEOUT);
        }

        /*
         * Si tous les rouleaux ont été arrétés, alors on contrôle si il n'y a pas gain,
         * et on récompense le joueur en conséquence.
         */
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

void BmManager::abortGame() {
	// Bloc pour éviter un dead lock par l'appel de boutonStop qui va
    // également créer un QMutexLocker sur stopMutex.
	{
		QMutexLocker lock(&stopMutex);
		timer.stop();

		/*
		 * Arrêt de tout les rouleaux d'un seul coup.
		 */
		for(; nextBarrelToStop < NB_BARREL; nextBarrelToStop++)
			barrels[nextBarrelToStop].terminate();
	}
    /*
     * Même si tous les rouleaux sont déjà arrêté, la méthode boutonStop()
     * est appelé, afin de profité de la partie contrôle de victoire de la
     * méthode.
     */
    boutonStop();
}

