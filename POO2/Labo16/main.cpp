/* 
 * File:   main.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: 
 *
 * Created on 18.05.16.
 */

#include <iostream>
#include "Controller.h"
#include "person/Child.h"
#include "person/Cop.h"
#include "person/Parent.h"
#include "person/Thief.h"

using namespace std;

int main() {
	// Liste des personnes
	list<const Person*> persons;
	persons.push_back(new Father("pere"));
	persons.push_back(new Mother("mere"));
	persons.push_back(new Boy("paul"));
	persons.push_back(new Boy("pierre"));
	persons.push_back(new Girl("julie"));
	persons.push_back(new Girl("jeanne"));
	persons.push_back(new Cop("policier"));
	persons.push_back(new Thief("voleur"));

	// Construction du controlleur
	Controller game(persons);

	// Boucle principale
	game.showMenu();
	game.display();
	while (!game.finished()) {
		game.nextTurn();
	}

	// Partie terminée
	game.display();
	cout << "Felicitation, vous avez termine la partie en " << game.turn() << " coups!" << endl;
	return 0;
}
