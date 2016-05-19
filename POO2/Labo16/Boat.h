/* 
 * File:   Boat.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_BOAT_H
#define LABO16_BOAT_H

#include "Container.h"
#include "Bank.h"
#include "ActionException.h"

/**
 * Le bateau
 */
class Boat : public Container {
private:
	/** Rive actuelle du bateau */
	Bank* _current;

	/** Capacité restante du bateau */
	size_t capacity;

public:
	Boat(const std::string& name, Bank* bank);

	/** Retourne la rive actuelle du bateau */
	Bank* currentBank() const;

	/** Vérifie si le bateau peut bouger */
	bool canMove() const;

	/** Déplace le bateau vers une autre rive */
	void moveTo(Bank* bank, bool force = false) throw (ActionException);

	// Redéfinition
	virtual void add(const Person* person, bool force = false) throw (ActionException);
	virtual void remove(const Person* person, bool force = false) throw (ActionException);
	virtual void moveEveryoneTo(Container& other, bool force = false) throw (ActionException);
};


#endif //LABO16_BOAT_H
