//
// Created by Bastien Clément on 18.05.16.
//

#include "Controller.h"

Controller::Controller(const list<const Person*> persons) : _turn(0), _left("Gauche"), _right("Droite"), _boat("Bateau", &_left) {
	for (const Person* person : persons) {
		_left.add(person);
	}
}

string Controller::serialize(const Container& container, const string& left, const string& right) const {
	string str = container.name() + ":" + left;
	for (auto person : container) str += " " + person->name();
	return str + right;
}

string Controller::serialize(const Boat& boat) const {
	return serialize(boat, " <", " >");
}

void Controller::showMenu() const {
	cout <<
		"p       : afficher\n"
		"e <nom> : embarquer\n"
		"d <nom> : debarquer\n"
		"m       : deplacer bateau\n"
		"r       : reinitialiser\n"
		"q       : quitter\n"
		"h       : menu"
	<< endl;
}

void Controller::display() const {
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << serialize(_left) << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << (_boat.currentBank() == &_left ? serialize(_boat) : "") << endl;
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << endl;
	cout << (_boat.currentBank() == &_right ? serialize(_boat) : "") << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << serialize(_right) << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << endl;
}

void Controller::nextTurn() {
	++_turn;
	while (true) {
		cout << _turn << "> ";

		string line;
		getline(cin, line);

		if (line.length() < 1) {
			showMenu();
			continue;
		}

		char cmd = line[0];

		switch (cmd) {
			case 'p':
				display();
				continue;

			case 'm':
				try {
					_boat.moveTo(_boat.currentBank() == &_right ? &_left : &_right);
				} catch (ActionException err) {
					cout << err.message() << endl;
					continue;
				}
				return;

			case 'r':
				_boat.moveEveryoneTo(_left, true);
				_right.moveEveryoneTo(_left, true);
				_boat.moveTo(&_left, true);
				return;

			case 'e':
			case 'd': {
				if (line.length() < 3) {
					showMenu();
					continue;
				}

				string name = line.substr(2);

				Container& source = (cmd == 'd') ? (Container&) _boat : (Container&) *(_boat.currentBank());
				Container& dest   = (cmd == 'e') ? (Container&) _boat : (Container&) *(_boat.currentBank());

				const Person* person = source.find(name);
				if (person == nullptr) {
					cout << ("Cette personne ne se trouve pas sur " + string(cmd == 'd' ? "le bateau" : "le rivage")) << endl;
					continue;
				}

				try {
					source.remove(person);
					try {
						dest.add(person);
					} catch (ActionException e) {
						source.add(person);
						throw e;
					}
				} catch (ActionException e) {
					cout << e.message() << endl;
					continue;
				}
				return;
			}

			case 'q':
				exit(0);

			default:
				showMenu();
				continue;
		}
	}
}

bool Controller::finished() const {
	return _left.empty() && _boat.empty();
}

unsigned int Controller::turn() const {
	return _turn;
}


