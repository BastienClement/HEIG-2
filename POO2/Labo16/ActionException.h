/* 
 * File:   ActionException.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Classe d'exception lancée lorsqu'une action de l'utilisateur
 * a laissé le jeu dans un état incohérent.
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_ACTIONEXCEPTION_H
#define LABO16_ACTIONEXCEPTION_H

#include <string>

using namespace std;

/**
 * Une exception produite suite à une action de l'utilisateur
 */
class ActionException {
private:
	const string _message;

public:
	ActionException(const string& message);
	const string& message() const;
};


#endif //LABO16_ACTIONEXCEPTION_H
