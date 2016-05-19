/* 
 * File:   Thief.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#include <iostream>
#include "Thief.h"
#include "PersonVisitor.h"
#include "../Container.h"

Thief::Thief(const string& name) : Person(name) {}

bool Thief::canDrive() const {
	return false;
}

void Thief::accept(PersonVisitor& visitor) const {
	visitor.visit(*this);
}

void Thief::validateState(const Container& container) const {
	class : public PersonVisitor {
	public:
		bool cop = false;
		bool family = false;

		virtual void visit(const FamilyMember&) { family = true; };
		virtual void visit(const Cop&) { cop = true; };
	} visitor;

	container.visit(visitor);

	if (visitor.family && !visitor.cop) {
		throw ActionException(
				"Le voleur ne peut pas se trouver avec un membre de la famille si le policier n'est pas present...");
	}
}
