/* 
 * File:   Thief.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Déclaration du voleur
 *
 * Le voleur surcharge la méthode validateState pour s'assurer de ne pas
 * rester avec un membre de la famille sans le policier.
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_THIEF_H
#define LABO16_THIEF_H

#include "Person.h"

/**
 * Le voleur
 */
class Thief : public Person {
public:
	Thief(const string& name);

	virtual bool canDrive() const;
	virtual void accept(class PersonVisitor& visitor) const;
	virtual void validateState(const class Container& container) const;
};

#endif //LABO16_THIEF_H
