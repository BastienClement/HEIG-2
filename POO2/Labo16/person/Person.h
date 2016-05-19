/* 
 * File:   Person.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_PERSON_H
#define LABO16_PERSON_H

#include <string>
#include "../Util.h"

using namespace std;

/**
 * Une personne
 */
class Person {
private:
	/** Nom de la personne */
	const string _name;

public:
	Person(const string& name);

	/** Indique si la personne peut conduire le bateau */
	virtual bool canDrive() const = 0;

	/** Valide l'état courant du container, relativement à cette personne */
	virtual void validateState(const class Container& container) const;

	/** Retourne le nom de la personne */
	const string& name() const;

	/** Accepte un visiteur */
	virtual void accept(class PersonVisitor&) const = 0;
};

#endif //LABO16_PERSON_H
