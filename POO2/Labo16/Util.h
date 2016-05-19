/*
 * File:   Util.h
 * Author: Bastien Clément & Alain Hardy
 *
 * Goal: Classes utilitaires
 *
 * Created on 18.05.16.
 */

#ifndef LABO16_UTIL_H
#define LABO16_UTIL_H

namespace Util {
	/**
	 * Défini un opérateur d'égalité basé sur l'identité des objets comparés
	 */
	template <typename Self>
	class IdentityEquality {
	public:
		bool operator == (const Self& other) {
			return this == &other;
		}

		bool operator != (const Self& other) {
			return this != &other;
		}
	};
}

#endif //LABO16_UTIL_H
