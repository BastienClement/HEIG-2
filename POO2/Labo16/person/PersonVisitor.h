/* 
 * File:   PersonVisitor.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Déclaration d'un visiteur de personne
 *
 * L'utilisation du visiteur pattern implémente le "double dispatch"
 * capable de résoudre les méthodes surchargée en fonction du type des
 * arguments à l'exécution.
 *
 * En d'autre mot, il est utile pour distinguer un Boy d'une Girl, lorsque
 * tout deux sont vus en tant que Person.
 *
 * Created on 18.05.16.
 */

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
