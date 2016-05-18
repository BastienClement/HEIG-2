//
// Created by Bastien Clément on 18.05.16.
//

#ifndef LABO16_UTIL_H
#define LABO16_UTIL_H

namespace Util {
	/**
	 * Inherit from this to have identity equality semantic
	 */
	template <typename Self>
	class IdentityEquality {
	public:
		bool operator == (const Self& other) {
			return this == &other;
		}
	};
}

#endif //LABO16_UTIL_H
