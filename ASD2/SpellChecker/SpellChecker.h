//
// Created by galedric on 16.01.2016.
//

#ifndef SPELLCHECKER_SPELLCHECKER_H
#define SPELLCHECKER_SPELLCHECKER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/**
 * Le SpellChecker est responsable de la gestion des E/S.
 * Il implémente l'ensemble de l'agorithme de correction à l'exception
 * du dictionnaire qu'il prend en tant que paramètre de template.
 */
template <typename Dictionary>
class SpellChecker {
private:
	/**
	 * Le dictionnaire qui servira à vérifier les mots rencontrés et générés.
	 * C'est une classe qui doit supporter les opérations .put() et .has()
	 * permettant d'ajouter un nouveau mot et de vérifier si un mot donné
	 * appartient à la liste.
	 */
	Dictionary dict;

	/**
	 * Retire tous les caractères qui ne sont pas des lettres ou
	 * un apostrophe dans la chaine passée en paramètre
	 */
	inline string normalize(const string& in) const {
		string clean = "";
		size_t len = in.length();

		for (size_t i = 0; i < len; i++) {
			char c = in[i];
			if (isCharAllowed(c, i, len)) {
				clean += tolower(c);
			}
		}

		return clean;
	}

	/**
	 * Vérifie si un caractère est alphabétique ou un apostrophe.
	 * Les apostrophe ne sont autorisés qu'en milieu de mot.
	 */
	inline bool isCharAllowed(char c, size_t pos, size_t len) const {
		return isalpha(c) || (c == '\'' && pos != 0 && pos != len - 1);
	}

	/**
	 * Vérifie un mot du texte
	 * Si le mot n'est pas correcte, une alternative sera recherchée et le mot
	 * sera inscrit dans le fichier de sortie.
	 */
	inline void check_word(const string& word_raw, ofstream& out) const {
		string word = normalize(word_raw);
		if (!dict.has(word)) {
			// Mot erroné
			out << "*" << word << "\n";

			// Une lettre en trop
			for (size_t i = 0; i < word.length(); i++) {
				guess(word.substr(0, i) + word.substr(i + 1, word.length() - i - 1), '1', out);
			}

			// Une lettre en moins
			for (size_t i = 0; i <= word.length(); i++) {
				string prefix = word.substr(0, i);
				string suffix = word.substr(i, word.length() - i);
				for (char c = 'a'; c <= 'z'; c++) {
					guess(prefix + c + suffix, '2', out);
				}
			}

			// Une lettre fausse
			for (size_t i = 0; i < word.length(); i++) {
				char orig = word[i];
				for (char c = 'a'; c <= 'z'; c++) {
					word[i] = c;
					guess(word, '3', out);
				}
				word[i] = orig;
			}

			// Deux lettre inversées
			for (size_t i = 0; i < word.length() - 1; i++) {
				swap(word[i], word[i+1]);
				guess(word, '4', out);
				swap(word[i], word[i+1]);
			}
		}
	}

	/**
	 * Vérifie si une modification du mot erroné à conduit à un mot correct
	 */
	inline void guess(const string& word, char type, ofstream& out) const {
		if (dict.has(word)) {
			out << type << ":" << word << "\n";
		}
	}

public:
	/**
	 * Constructeur
	 * Charge le fichier de définition du dictionnaire
	 */
	SpellChecker(const string& path) {
		ifstream file(path, ios::in);
		string line;
		while (getline(file, line)) {
			string clean = normalize(line);
			if (clean != "") dict.put(clean);
		}
	}

	/**
	 * Vérifie un fichier texte
	 */
	void check(const string& path) const {
		ifstream file(path, ios::in);
		if (!file.good()) throw "Unable to open file!";

		ofstream out("err_" + path, ios::out | ios::trunc);

		string line;
		while (getline(file, line)) {
			// Début du mot et flag "dans le mot"
			size_t word_start = 0;
			bool in_word = false;
			char c;

			// Identification des mots
			for (size_t i = 0; i < line.length(); i++) {
				c = line[i];
				if (isCharAllowed(c, in_word ? i - word_start : 0, -1)) {
					if (!in_word) {
						word_start = i;
						in_word = true;
					}
				} else {
					if (in_word) {
						size_t word_end = c == '\'' ? i - 1 : i;
						check_word(line.substr(word_start, word_end - word_start), out);
						in_word = false;
					}
				}
			}

			if (in_word) {
				size_t word_end = c == '\'' ? line.length() - 1 : line.length();
				check_word(line.substr(word_start, word_end - word_start), out);
			}
		}
	}
};

#endif //SPELLCHECKER_SPELLCHECKER_H
