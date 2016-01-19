#include <iostream>
#include <unordered_set>
#include <string>
#include <chrono>
#include "SpellChecker.h"
#include "AVLTree.h"
#include "TernarySearchTrie.h"

using namespace std;
using namespace std::chrono;

/**
 * Wrapper pour un dictionnaire basé sur une structure STL
 * Dans notre cas, unordered_set
 */
class STLDictionary {
private:
	unordered_set<string> words;
public:
	void put(string word) { words.insert(word); }
	bool has(string word) const { return words.find(word) != words.end(); }
};

/**
 * Wrapper pour un dictionnaire basé sur un TST
 */
class TSTDictionary {
private:
	TST<bool> tst;
public:
	void put(string word) { tst.put(word, true); }
	bool has(string word) const { return tst.contains(word); }
};

/**
 * Timer utility
 */
class Timer {
private:
	steady_clock::time_point tp_start;
	steady_clock::time_point tp_checkpoint;
	steady_clock::time_point tp_pause;
	double paused_total;
	double paused_checkpoint;

public:
	void start() {
		tp_start = tp_checkpoint = steady_clock::now();
		paused_total = paused_checkpoint = 0;
	}

	void pause() {
		tp_pause = steady_clock::now();
	}

	void resume() {
		double pause = duration_cast<duration<double>>(steady_clock::now() - tp_pause).count();
		paused_total += pause;
		paused_checkpoint += pause;
	}

	double checkpoint() {
		steady_clock::time_point now = steady_clock::now();
		double time = duration_cast<duration<double>>(now - tp_checkpoint).count()- paused_checkpoint;
		tp_checkpoint = now;
		paused_checkpoint = 0;
		return time;
	}

	double time() {
		steady_clock::time_point now = steady_clock::now();
		return duration_cast<duration<double>>(now - tp_start).count() - paused_total;
	}
};

template <typename DictImpl>
void do_test() {
	Timer t;
	try {
		t.start();

		SpellChecker<DictImpl> sc("dictionary.txt");
		cout << endl << "Dictionary loading phase done in " << t.checkpoint() << " seconds." << endl;

		string file;
		cout << "Enter file name: ";
		t.pause();
		cin >> file;
		t.resume();

		sc.check(file);
		cout << "Spell checking phase done in " << t.checkpoint() << " seconds." << endl;
		cout << endl << "Errors written in: 'err_" << file << "'" << endl;

		cout << "Done in " << t.time() << " seconds." << endl;
	}
	catch (const char* error) {
		cerr << "Error: " << error << endl;
	}
}

int main() {
	do {
		cout << "-------------------------------------------" << endl;
		cout << "[1] STLDictionary (unordered_set)" << endl;
		cout << "[2] TSTDictionary (Ternary Search Trie)" << endl;
		cout << "[Other] Quit" << endl;
		cout << "Select dictionary implementation to use: ";

		string choice;
		cin >> choice;

		if (choice.empty()) return 0;
		switch (choice[0]) {
			case '1': do_test<STLDictionary>(); break;
			case '2': do_test<TSTDictionary>(); break;
			default: return 0;
		}
	} while(1);
}