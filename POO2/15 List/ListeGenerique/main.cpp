/* 
 * File:   main.cpp
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal : Test sur la liste générique doublement chainée.
 *
 * Created on 17. avril 2016, 22:56
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include "List.h"
#include <stdexcept>

using namespace std;

class Person{
public:
   string name;
   Person(string n): name(n){};
};

int main() {
   try{
      List<string> l;
      l.append("un");
      l.append("deux");
      l.append("trois");
      cout << "Taille : " << l.size() << endl;
      for (List<string>::Iterator it = l.begin(); it != l.end(); it++)
         cout << *it << " ";
      cout << endl;
      
      l.remove(2);
      l.remove("deux");      
      cout << "Taille apres suppression : " << l.size() << endl;
      cout << endl;

      List<Person*> lp;
      lp.append(new Person("Alice"));
      lp.append(new Person("Bob"));
      lp.append(new Person("Carla"));
      lp.append(new Person("Damien"));

      List<Person*> lp2;
      lp2= lp;
      for(List<Person*>::Iterator it = lp.begin(); it != lp.end(); it++)
         cout << (*it)->name << " ";
      cout << endl;
      
   } catch(const std::runtime_error& ex) {
      cout << ex.what() << endl;
   }
      
   return EXIT_SUCCESS;
}

