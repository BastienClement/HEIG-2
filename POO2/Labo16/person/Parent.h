//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_PARENT_H
#define LABO16_PARENT_H

#include "Person.h"
#include "FamilyMember.h"

class Parent : public FamilyMember {
public:
	Parent(const string& name);
	virtual bool canDrive() const;
};

class Father : public Parent {
public:
	Father(const string& name);
	virtual void accept(class PersonVisitor& visitor) const;
};

class Mother : public Parent {
public:
	Mother(const string& name);
	virtual void accept(class PersonVisitor& visitor) const;
};

#endif //LABO16_PARENT_H
