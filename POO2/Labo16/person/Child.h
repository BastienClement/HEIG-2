//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_CHILD_H
#define LABO16_CHILD_H

#include "Person.h"
#include "FamilyMember.h"

class Child : public FamilyMember {
public:
	Child(const string& name);
	virtual bool canDrive() const;
};

class Boy : public Child {
public:
	Boy(const string& name);
	virtual void accept(class PersonVisitor& visitor) const;
	virtual void validateState(const class Container& container) const;
};

class Girl : public Child {
public:
	Girl(const string& name);
	virtual void accept(class PersonVisitor& visitor) const;
	virtual void validateState(const class Container& container) const;
};

#endif //LABO16_CHILD_H
