/* 
 * File:   cstring.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal : Implémentation des méthodes de la String.
 * 
 * Created on 10. mars 2016, 11:31
 */

#include "cstring.h"
#include <string.h>
#include <algorithm>

/*
 * Création d'un String vide.
 */
String::String() {
	_size = 0;
	_str = new char[1];
	_str[0] = '\0';
}

/*
 * Création d'un String à partir d'une chaîne de caractère.
 */
String::String(const char* cs) {
	_size = strlen(cs);
	_str = new char[_size + 1];
	strcpy(_str, cs);
}

/*
 * Création d'un String à partir d'une autre instance de String.
 */
String::String(const String& s) {
	_str = new char[s._size + 1];
	_size = s._size;
	*this = s;
}

/*
 * Création d'un String à partir d'un caractère.
 */
String::String(const char c) {
	_size = 1;
	_str = new char[2];
	_str[0] = c;
	_str[1] = '\0';
}

/*
 * Création d'un String à partir d'une valeur entière.
 */
String::String(const int i) {
	char buffer[15];
        snprintf(buffer, sizeof(buffer), "%d", i);

	_size = strlen(buffer);
	_str = new char[_size + 1];
	strcpy(_str, buffer);
}

/*
 * Création d'un String à partir d'une valeur réele.
 */
String::String(const double d) {
	char buffer[30];
	snprintf(buffer, sizeof(buffer), "%.15g", d);

	_size = strlen(buffer);
	_str = new char[_size + 1];
	strcpy(_str, buffer);
}

/*
 * Création d'un String à partir d'une booléan.
 */
String::String(const bool b) {
	_size = b ? strlen("true") : strlen("false");

	_str = new char[_size + 1];
	strcpy(_str, b ? "true" : "false");
	_str[_size] = '\0';
}

/*
 * Création d'un String à partir d'un autre String, en précisant la position de 
 * départ ainsi que le nombre de caractères à prendre après le départ.
 */
String::String(const String& str, size_t start, size_t len) : String(str.c_str(), start, len) { }

/*
 * Création d'un String à partir d'une chaîne de caractères, en précisant la position
 * de départ ainsi que le nombre de caractères à prendre après le départ.
 */
String::String(const char* cs, size_t start, size_t len) {
	size_t cs_len = strlen(cs);

	// On s'assure que start ne soit pas plus long que la chaîne.
	if (start > cs_len) {
		_size = 0;
		_str = new char[1];
		_str[0] = '\0';
		return;
	}
        
        // Assure d'avoir une chaîne cohérente, dans le cas où une taille plus grande
        // que le nombre de caractères disponible est demandée.
	_size = std::min(cs_len - start, len);
	_str = new char[_size + 1];
	strncpy(_str, cs + start, _size);
	_str[_size] = '\0';
}

String::~String() {
	delete[] _str;
}

/*
 * Retourne la taille du String. La taille correspont au nombres de caractères 
 * effectifs du String.
 */
const int String::size() const {
	return _size;
}

/*
 * Retourne une représentation sous forme de chaîne de caractères du String.
 */
const char* String::c_str() const {
	return _str;
}

/*
 * Retourne un caractère à une position donnée du String. 
 * Lance une exception si la position demandé est en dehors de la portée du String.
 */
char& String::at(size_t pos) throw(const std::runtime_error&) {
	if (pos >= _size || pos < 0)
		throw std::runtime_error("Out of range.");
	return _str[pos];
}

/*
 * Retourne un caractère en lecture à une position donnée du String.
 * Lance une exception si la position demandé est en dehors de la portée du String.
 */
const char& String::at(size_t pos) const throw(const std::runtime_error&) {
	if (pos >= _size || pos < 0)
		throw std::runtime_error("Out of range.");
	return _str[pos];
}

/*
 * Compare le String et une chaîne de caractère, et détermine s'ils sont 
 * identiques.
 */
bool String::isEqual(const char* charArray) const {
	return !strcmp(_str, charArray);
}

/*
 * Compare le String avec une autre instance de String afin de déterminer s'ils sont
 * identiques.
 */
bool String::isEqual(const String& s) const {
	return isEqual(s._str);
}

/*
 * Affecte une chaîne de caractères au String.
 */
String& String::assign(const char* charArray) {
         if(_size != strlen(charArray)) {
            _size = strlen(charArray);
            delete[] _str;
            _str = new char[_size+1];
         }

         strcpy(_str, charArray);
         return *this;  
}

/*
 * Affecte le contenu d'un String à l'instance d'un String.
 */
String& String::assign(const String& s) {
         return assign(s._str);
}

/*
 * Concatène le String à une chaine de caractères.
 */
String& String::append(const char* charArray) {
	char* temp = new char[_size + strlen(charArray) + 1];
	strcpy(temp, _str);
	strcpy(temp + _size, charArray);

	delete[] _str;
	_str = temp;
	_size += strlen(charArray);

	_str[_size] = '\0';

	return *this;
}

/*
 * Concatène le String à une autre instance de String.
 */
String& String::append(const String& s) {        
	return append(s._str);;
}

/*
 * Comparaison du String à une chaîne de caractères.
 */
bool String::operator==(const char* charArray) const {
	return isEqual(charArray);
}

/*
 * Comparaison du String à un autre String.
 */
bool String::operator==(const String& s) const {
	return isEqual(s);
}

/*
 * Affectation au String d'une chaîne de caractères.
 */
String& String::operator=(const char* charArray) {
	return assign(charArray);
}

/*
 * Affectation au String d'un autre String.
 */
String& String::operator=(const String& s) {
	return assign(s);
}

/*
 * Concaténation du String à une chaîne de caractères.
 */
String String::operator+(const char* charArray) const {
	return String(*this).append(charArray);
}

/*
 * Concaténation du String à un autre String.
 */
String String::operator+(const String& s) const {
	return String(*this).append(s);
}

/*
 * Concaténation et affectation du String avec une chaîne de caractères.
 */
String& String::operator+=(const char* charArray) {
	return append(charArray);
}

/*
 * Concaténation et affectation du String avec une autre instance de String.
 */
String& String::operator+=(const String& s) {
	return append(s);
}

/*
 * Récupératon d'une portion du String, partant de "start" allant juqu'à 
 * "end"(non compris).
 * Lance une exception dans le cas où l'interval demandée n'est pas cohérente,
 * ou si elle dépasse la taille du String.
 */
String String::slice(size_t start, size_t end) const throw(const std::runtime_error&) {
	if (start > end || end > _size)
		throw std::runtime_error("Invalid range.");
	return String(*this, start, end - start);
}

/*
 * Surcharge de l'opérateur de flux de sortie.
 */
std::ostream& operator<<(std::ostream& os, const String& s) {
	return os << s._str;
}
