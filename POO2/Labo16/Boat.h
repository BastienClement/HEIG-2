//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_BOAT_H
#define LABO16_BOAT_H

#include "Container.h"
#include "Bank.h"
#include "ActionException.h"

class Boat : public Container {
private:
	Bank* _current;
	size_t capacity;

public:
	Boat(const std::string& name, Bank* bank);
	Bank* currentBank() const;

	bool canMove() const;
	void moveTo(Bank* bank, bool force = false) throw (ActionException);

	virtual void add(const Person* person, bool force = false) throw (ActionException);
	virtual void remove(const Person* person, bool force = false) throw (ActionException);
	virtual void moveEveryoneTo(Container& other, bool force = false) throw (ActionException);
};


#endif //LABO16_BOAT_H
