//
// Created by galedric on 16.01.2016.
//

#ifndef SPELLCHECKER_TERNARYSEARCHTRIE_H
#define SPELLCHECKER_TERNARYSEARCHTRIE_H

#include <string>

template <typename Value>
class TST {
private:
	/**
	 * Un noeud interne de l'arbre
	 */
	struct Node {
		Node(char ch) : c(ch) {};
		char c;
		Value value;
		bool hasValue = false;
		Node *left = nullptr,
		     *mid = nullptr,
		     *right = nullptr;
	};

	/**
	 * Racine du Ternary Search Tree
	 */
	Node* root = nullptr;

	/**
	 * Méthode interne d'insertion
	 */
	Node* put(Node* x, std::string key, Value val, int d) {
		char c = key[d];
		if (x == nullptr) { x = new Node(c); }
		if (c < x->c) {
			x->left = put(x->left, key, val, d);
		} else if (c > x->c) {
			x->right = put(x->right, key, val, d);
		} else if (d < key.length() - 1) {
			x->mid = put(x->mid, key, val, d + 1);
		} else {
			x->hasValue = true;
			x->value = val;
		}
		return x;
	}

	/**
	 * Méthode interne de recherche du noeud correspondant à une clé
	 */
	Node* get(Node* x, std::string key, int d) const {
		if (x == nullptr) return nullptr;
		char c = key[d];
		if (c < x->c) {
			return get(x->left, key, d);
		} else if (c > x->c) {
			return get(x->right, key, d);
		} else if (d < key.length() - 1) {
			return get(x->mid, key, d + 1);
		} else {
			return x;
		}
	}

public:
	/**
	 * Ajoute une paire clé-valeur dans la structure
	 */
	void put(std::string key, Value value) {
		root = put(root, key, value, 0);
	}

	/**
	 * Retourne la valeur associée à une clé, si celle-ci existe
	 */
	Value get(std::string key) const {
		Node* x = get(root, key, 0);
		if (x == nullptr || !x->hasValue) throw nullptr;
		return x->value;
	}

	/**
	 * Vérifie si une clé est contenue dans la structure
	 */
	bool contains(std::string key) const {
		Node* x = get(root, key, 0);
		return x != nullptr && x->hasValue;
	}
};

#endif //SPELLCHECKER_TERNARYSEARCHTRIE_H
