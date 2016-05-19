/* 
 * File:   Cop.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_COP_H
#define LABO16_COP_H

#include "Person.h"

/**
 * Le policier
 */
class Cop : public Person {
public:
	Cop(const string& name);
	virtual bool canDrive() const;
	virtual void accept(class PersonVisitor& visitor) const;
};

#endif //LABO16_COP_H
