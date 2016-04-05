/* 
 * File:   main.cpp
 * Author: Alain
 *
 * Created on 10. mars 2016, 11:24
 */

#include <cstdlib>
#include <ostream>
#include <stdexcept>

#include "cstring.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

   /*
   String();
   String(const char*);
   String(const String&);
   String(const char);
   String(const int);
   String(const bool);
   ~String();
   
   const int size() const;
   const char* c_str() const;
   char& at(size_t);
   const char& at(size_t) const;
   
   bool operator==(const char*);
   bool operator==(const String&);
   String& operator=(const String&);
   String& operator+(const String&);
   String& operator+=(const String&);
   
   String& between(int, int) const;
   
   static char* to_charArray(const int);
    */
   String sVide;
   String sCharEtoile("Bonjour");
   String sString(sCharEtoile);
   String sChar('A');
   String sInt(123456);
   String sBool(true);   
   
   String* sArray[] = {&sVide, &sCharEtoile, &sString, &sChar, &sInt, &sBool};
   
   for(int i = 0; i < 6 ; i++) {
      cout << "Contenu : " << *(sArray[i]) << endl;
      cout << "Taille : " << sArray[i]->size() << endl << endl;
   }
   
   try{
      sCharEtoile.at(sCharEtoile.size()+1);
   }catch(runtime_error ex) {
      cerr << ex.what() << endl;
   }
   
   cout << "Conversion en char* + affichage" << endl;
   for(int i = 0; i < 6; i++) {
      cout << sArray[i]->c_str() << endl;
   }
   
   
   cout << endl << "Test d'egalite" << endl;
   
   cout << sCharEtoile << " == " << sString << " ? " << String(sCharEtoile == sString) << endl;
   cout << sString << " == " << sChar << " ? " << String(sString == sChar) << endl;
   cout << sInt << " == " << 123 << " ? " << String(sInt == 123) << endl;
   cout << sInt << " == " << 123456 << " ? " << String(sInt == 123456) << endl;
   
   cout << endl << "Operateur =" << endl;
   cout << "Avant : " << sString << endl;
   sString = "ca va ?";
   cout << "Apres : " << sString << endl;
   
   cout << endl << "Operateur d'addition" << endl;
   cout << "Avant : " << sCharEtoile << endl;
   sCharEtoile = sCharEtoile + " " + sString;
   cout << "Apres : " << sCharEtoile << endl;
   cout << "Avant : " << sInt << endl;
   sInt += 789;
   cout << "Apres : " << sInt << endl;
   
   cout << endl << "SubString" << endl;
   cout << "Sous chaîne de \"" << sCharEtoile << "\" de 2 à 10 : " << sCharEtoile.between(2,10) << endl;
   
   
   return EXIT_SUCCESS;
}

