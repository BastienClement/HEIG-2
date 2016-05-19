//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_PERSON_H
#define LABO16_PERSON_H

#include <string>
#include "../Util.h"

using namespace std;

class Person {
private:
	const string _name;

public:
	Person(const string& name);

	virtual bool canDrive() const = 0;
	virtual void validateState(const class Container& container) const;

	const string& name() const;

	virtual void accept(class PersonVisitor&) const = 0;
};

#endif //LABO16_PERSON_H
