/* 
 * File:   ActionException.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#include "ActionException.h"

ActionException::ActionException(const string& message) : _message(message) {}

const string& ActionException::message() const {
	return _message;
}
