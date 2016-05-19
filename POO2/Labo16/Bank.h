/* 
 * File:   Bank.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
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
