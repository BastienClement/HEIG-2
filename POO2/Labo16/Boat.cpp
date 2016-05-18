//
// Created by Bastien Clément on 18.05.16.
//

#include "Boat.h"
#include "person/Person.h"

Boat::Boat(const std::string& name, Bank* bank) : Container(name), _current(bank), capacity(2) { }

Bank* Boat::currentBank() const {
	return _current;
}

bool Boat::canMove() const {
	for (const Person* person : *this) {
		if (person->canDrive()) return true;
	}
	return false;
}

void Boat::moveTo(Bank* bank, bool force) throw (ActionException) {
	if (!force && !canMove()) throw ActionException("Personne ne peut piloter le bateau!");
	_current = bank;
}

void Boat::add(const Person* person, bool force) throw (ActionException) {
	if (capacity == 0) throw ActionException("Das Boot ist voll!");
	Container::add(person, force);
	capacity--;
}

void Boat::remove(const Person* person, bool force) throw (ActionException) {
	if (empty()) throw ActionException("Le bateau est vide!");
	Container::remove(person, force);
	capacity++;
}

void Boat::moveEveryoneTo(Container& other, bool force) throw (ActionException) {
	capacity += persons.size();
	Container::moveEveryoneTo(other, force);
}






