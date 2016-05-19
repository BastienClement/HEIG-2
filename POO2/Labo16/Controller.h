/* 
 * File:   Controller.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Déclaration du controlleur du jeu
 *
 * Le controlleur est responsable de la lecture des entrées et de l'exécution
 * des commandes du l'utilisateur. Il s'assure de la conservation d'un état
 * cohérent tout au long de la partie.
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_CONTROLLER_H
#define LABO16_CONTROLLER_H

#include <iostream>
#include "Bank.h"
#include "Boat.h"
#include "person/Person.h"
#include "ActionException.h"

using namespace std;

/**
 * Controlleur du jeu
 */
class Controller {
private:
	/** Tour actuel */
	unsigned int _turn;

	/** Les deux rives et le bateau */
	Bank _left;
	Bank _right;
	Boat _boat;

	/** Sérialise les contenneurs en chaine de caractères */
	string serialize(const Container& container, const string& left = "", const string& right = "") const;
	string serialize(const Boat& boat) const;

public:
	/**
	 * Construit un controlleur à partir d'une liste de personne donnée
	 */
	Controller(const list<const Person*> persons);

	/**
	 * Affiche le menu du jeu
	 */
	void showMenu() const;

	/**
	 * Affiche l'état courrant du jeu
	 */
	void display() const;

	/**
	 * Exécute le tour suivant
	 */
	void nextTurn();

	/**
	 * Indique si la partie est terminée
	 */
	bool finished() const;

	/**
	 * Indique le nombre de tour joués
	 */
	unsigned int turn() const;
};


#endif //LABO16_CONTROLLER_H
