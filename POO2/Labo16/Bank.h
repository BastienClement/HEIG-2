/* 
 * File:   Bank.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Déclaration d'une rive
 *
 * Cette classe ne fait rien de plus que Container, mais permet de
 * distinguer une rive d'un bateau au niveau des types. Il n'est par
 * exemple pas possible de déplacer un bateau vers un bateau plutôt
 * qu'une rive.
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_BANK_H
#define LABO16_BANK_H

#include "Container.h"

/**
 * Une rive
 */
class Bank : public Container {
public:
	Bank(const std::string& name);
};


#endif //LABO16_BANK_H
