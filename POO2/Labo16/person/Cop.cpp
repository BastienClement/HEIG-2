//
// Created by Bastien Clément on 18.05.16.
//

#include "Cop.h"
#include "PersonVisitor.h"

Cop::Cop(const string& name) : Person(name) {}

bool Cop::canDrive() const {
	return true;
}

void Cop::accept(PersonVisitor& visitor) const {
	visitor.visit(*this);
}
