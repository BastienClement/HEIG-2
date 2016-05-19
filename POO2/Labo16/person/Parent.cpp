/* 
 * File:   Parent.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#include "Parent.h"
#include "PersonVisitor.h"

Parent::Parent(const string& name) : FamilyMember(name) {}

bool Parent::canDrive() const {
	return true;
}

//
// Father
//

Father::Father(const string& name) : Parent(name) {}

void Father::accept(PersonVisitor& visitor) const {
	visitor.visit(*this);
}

//
// Mother
//

Mother::Mother(const string& name) : Parent(name) {}

void Mother::accept(PersonVisitor& visitor) const {
	visitor.visit(*this);
}
