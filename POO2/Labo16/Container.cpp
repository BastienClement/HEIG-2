//
// Created by Bastien Clément on 18.05.16.
//

#include "Container.h"
#include "person/PersonVisitor.h"
#include "person/Person.h"

Container::Container(const std::string& name) : _name(name) { }

template<typename Function>
void Container::validate(Function rollback) {
	for (const Person* person : *this) {
		try {
			person->validateState(*this);
		} catch (ActionException e) {
			rollback();
			throw e;
		}
	}
}

const Person* Container::find(string name) const {
	for (const Person* person : *this) {
		if (person->name() == name) return person;
	}
	return nullptr;
}

bool Container::empty() const {
	return persons.begin() == persons.end();
}

void Container::add(const Person* person, bool force) throw (ActionException) {
	persons.push_back(person);

	if (!force) {
		validate([&]() { persons.pop_back(); });
	}
}

void Container::remove(const Person* person, bool force) throw (ActionException) {
	persons.remove(person);

	if (!force) {
		validate([&]() { persons.push_back(person); });
	}
}

void Container::moveEveryoneTo(Container& other, bool force) throw (ActionException) {
	// On s'assure qu'on ne déplace pas tout le monde vers soi-même
	if (*this == other) return;

	for (const Person* person : *this) {
		other.add(person, force);
	}

	persons.clear();
}

Container::iterator Container::begin() const {
	return persons.begin();
}

Container::iterator Container::end() const {
	return persons.end();
}

void Container::visit(PersonVisitor& visitor) const {
	for (const Person* person : *this) {
		person->accept(visitor);
	}
}

const std::string& Container::name() const {
	return _name;
}


