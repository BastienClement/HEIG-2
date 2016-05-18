//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_CONTROLLER_H
#define LABO16_CONTROLLER_H

#include <iostream>
#include "Bank.h"
#include "Boat.h"
#include "person/Person.h"
#include "ActionException.h"

using namespace std;

class Controller {
private:
	unsigned int _turn;
	Bank _left;
	Bank _right;
	Boat _boat;

	string serialize(const Container& container, const string& left = "", const string& right = "") const;
	string serialize(const Boat& boat) const;

public:
	Controller(const list<const Person*> persons);

	void showMenu() const;
	void display() const;
	void nextTurn();
	bool finished() const;
	unsigned int turn() const;
};


#endif //LABO16_CONTROLLER_H
