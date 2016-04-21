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

using namespace std;

class Person{
public:
   string name;
   Person(string n): name(n){};
};

int main() {
   List<string> l;
   l.append("un");
   l.append("deux");
   l.append("trois");
   for (List<string>::Iterator it = l.begin(); it != l.end(); it++)
      cout << *it << " ";
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
      
   return EXIT_SUCCESS;
}

