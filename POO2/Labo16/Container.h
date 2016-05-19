/* 
 * File:   Container.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_CONTAINER_H
#define LABO16_CONTAINER_H

#include <string>
#include <list>
#include "ActionException.h"
#include "Util.h"

using namespace std;

/**
 * Un container de personnes, classe de base pour le bateau et les rives
 */
class Container : public Util::IdentityEquality<Container> {
public:
	/** Type de la liste des personnes */
	typedef std::list<const class Person*> list;

	/** Type de l'itérateur retourné par begin et end */
	typedef list::const_iterator iterator;

private:
	/** Nom du container */
	const string _name;

	/** Valide l'état courant, et appel la fonction de rollback si l'état n'est pas cohérent */
	template<typename Function>
	void validate(Function rollback);

protected:
	/** Liste des personnes dans ce container */
	list persons;

public:
	Container(const string& name);

	/** Trouve la personne avec un nom donné */
	const Person* find(string name) const;

	/** Indique si le container est vide */
	bool empty() const;

	/**
	 * Ajoute une nouvelle personne dans ce container
	 * Si force est true, aucune validation n'est effectuée
	 */
	virtual void add(const Person* person, bool force = false) throw (ActionException);

	/**
	 * Retire une personne dans ce container
	 * Si force est true, aucune validation n'est effectuée
	 */
	virtual void remove(const Person* person, bool force = false) throw (ActionException);

	/**
	 * Déplace toutes les personnes de ce container dans un autre container
	 * Si force est true, aucune validation n'est effectuée
	 */
	virtual void moveEveryoneTo(Container& other, bool force = false) throw (ActionException);

	/** Itérateur au début de la collection */
	iterator begin() const;

	/** Itérateur sur la fin de la collection */
	iterator end() const;

	/** Visite chaque personne avec le visiteur donné */
	void visit(class PersonVisitor& visitor) const;

	/** Retourne le nom de ce container */
	const std::string& name() const;
};

#endif //LABO16_CONTAINER_H
