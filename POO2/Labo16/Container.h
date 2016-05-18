//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_CONTAINER_H
#define LABO16_CONTAINER_H

#include <string>
#include <list>
#include "ActionException.h"
#include "Util.h"

using namespace std;

class Container : public Util::IdentityEquality<Container> {
public:
	using list = std::list<const class Person*>;
	using iterator = list::const_iterator;

private:
	const std::string _name;

	template<typename Function>
	void validate(Function rollback);

protected:
	list persons;

public:
	Container(const string& name);

	const Person* find(string name) const;
	bool empty() const;

	virtual void add(const Person* person, bool force = false) throw (ActionException);
	virtual void remove(const Person* person, bool force = false) throw (ActionException);
	virtual void moveEveryoneTo(Container& other, bool force = false) throw (ActionException);

	iterator begin() const;
	iterator end() const;

	void visit(class PersonVisitor& visitor) const;

	const std::string& name() const;
};

#endif //LABO16_CONTAINER_H
