//
// Created by Bastien Clément on 18.05.16.
//

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
