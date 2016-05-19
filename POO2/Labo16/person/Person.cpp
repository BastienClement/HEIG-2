/* 
 * File:   Person.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#include "Person.h"

Person::Person(const string& name) : _name(name) {}

void Person::validateState(const class Container& container) const {}

const string& Person::name() const {
	return _name;
}
