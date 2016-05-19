//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_PERSONVISITOR_H
#define LABO16_PERSONVISITOR_H

class FamilyMember;
class Child;
class Parent;
class Boy;
class Girl;
class Father;
class Mother;
class Cop;
class Thief;

/**
 * Un visiteur de personne
 * Les implémentations par défaut de ces méthodes ne font rien
 *
 * Les implémentations par défaut de Boy/Girl et Father/Mother appelent
 * les méthodes Child et Parent, et celles-ci appellent FamilyMember
 */
class PersonVisitor {
public:
	virtual void visit(const FamilyMember&);
	virtual void visit(const Child& child);
	virtual void visit(const Parent& parent);

	virtual void visit(const Boy& boy);
	virtual void visit(const Girl& girl);
	virtual void visit(const Father& father);
	virtual void visit(const Mother& mother);
	virtual void visit(const Cop&);
	virtual void visit(const Thief&);
};

#endif //LABO16_PERSONVISITOR_H
