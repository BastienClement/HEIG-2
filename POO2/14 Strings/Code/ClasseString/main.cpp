/* 
 * File:   main.cpp
 * Author: Alain
 *
 * Created on 10. mars 2016, 11:24
 */

#include <cstdlib>
#include <ostream>
#include <stdexcept>
#include <limits>

#include "cstring.h"

using namespace std;

/*
 * 
 */
int main() {

	String sVide;
	String sCharEtoile("Bonjour");
	String sString(sCharEtoile);
	String sChar('A');
	String sInt(123456);
	String sDouble(3.14);
	String sBool(true);

	String* sArray[] = {&sVide, &sCharEtoile, &sString, &sChar, &sInt, &sBool};

	cout << "Affichage du contenu et de la taille des differents String cree" << endl;
	for (int i = 0; i < 6; i++) {
		cout << "Contenu : " << *(sArray[i]) << endl;
		cout << "Taille : " << sArray[i]->size() << endl << endl;
	}


	cout << endl << "Acces a un element du String" << endl;
	try {
		cout << "Acces a l'element 2 de \"" << sCharEtoile << "\" : ";
		cout << sCharEtoile.at(2) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}
	try {
		cout << "Acces a l'element size()+1 de \"" << sCharEtoile << "\" : ";
		cout << sCharEtoile.at(sCharEtoile.size() + 1) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}
	try {
		cout << "Acces a l'element -1 de \"" << sCharEtoile << "\" : ";
		cout << sCharEtoile.at(-1) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}


	cout << endl << "Modification d'un element du String" << endl;
	try {
		cout << "Modification de l'element 2 de \"" << sCharEtoile << "\" par A : ";
		sCharEtoile.at(2) = 'A';
		cout << sCharEtoile << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}
	try {
		cout << "Modification de l'element 20 de \"" << sCharEtoile << "\" par Z : ";
		sCharEtoile.at(20) = 'Z';
		cout << sCharEtoile << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}


	cout << endl << "Conversion en char* + affichage" << endl;
	for (int i = 0; i < 6; i++) {
		cout << sArray[i]->c_str() << endl;
	}


	cout << endl << "Test d'egalite" << endl;
	cout << sCharEtoile << " == " << sString << " ? " << String(sCharEtoile == sString) << endl;
	cout << sString << " == " << sChar << " ? " << String(sString == sChar) << endl;
	cout << sInt << " == " << 123 << " ? " << String(sInt == 123) << endl;
	cout << sInt << " == " << 123456 << " ? " << String(sInt == 123456) << endl;


	cout << endl << "Affectation" << endl;
	cout << "Avant : " << sString << endl;
	sString = "ca va ?";
	cout << "Apres : " << sString << endl;


	cout << endl << "Concatenation" << endl;
	cout << "sCharEtoile avant : " << sCharEtoile << endl;
	sCharEtoile = sCharEtoile + " " + sString;
	cout << "sCharEtoile apres : " << sCharEtoile << endl;
	cout << "sInt avant : " << sInt << endl;
	sInt += 789;
	cout << "sInt apres : " << sInt << endl;


	cout << endl << "Sous-chaine" << endl;
	try {
		cout << "Sous chaîne de \"" << sCharEtoile << "\" de 2 à 10 : ";
		cout << sCharEtoile.between(2, 10) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "Sous chaine de \"" << sCharEtoile << "\" de 10 à 2 : ";
		cout << sCharEtoile.between(10, 2) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "Sous chaine de \"" << sCharEtoile << "\" de 2 à size()+1 : ";
		cout << sCharEtoile.between(2, sCharEtoile.size() + 1) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "Sous chaine de \"" << sCharEtoile << "\" de -1 à 10 : ";
		cout << sCharEtoile.between(-1, 10) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}

	try {
		cout << "Sous chaine de \"" << sCharEtoile << "\" de -10 à -2 : ";
		cout << sCharEtoile.between(-10, -2) << endl;
	} catch (runtime_error ex) {
		cout << ex.what() << endl;
	}

	return EXIT_SUCCESS;
}

