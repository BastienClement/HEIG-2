/* 
 * File:   FamilyMember.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Déclaration d'un membre de la famille
 *
 * Cette classe est utilisée par le voleur pour gérer de façon
 * unifiée tous les membres de la famille.
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_FAMILYMEMBER_H
#define LABO16_FAMILYMEMBER_H

#include "Person.h"

/**
 * Un membre de la famille
 */
class FamilyMember : public Person {
public:
	FamilyMember(const string& name);
};

#endif //LABO16_FAMILYMEMBER_H
