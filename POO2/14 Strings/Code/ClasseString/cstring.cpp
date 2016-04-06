/* 
 * File:   cstring.cpp
 * Author: Alain
 * 
 * Created on 10. mars 2016, 11:31
 */

#include "cstring.h"
#include <string.h>
#include <math.h>

char* String::to_charArray(const int number) {
   if(number == 0)
      return "0\0";
   
   bool isNegative = number < 0;   
   int tempNumber = number;
   
   if(isNegative) 
      tempNumber *= -1;
   
   int length = log10(tempNumber)+1+isNegative;
   
   char* strg = new char[length+1];
   
   for(int i = 0 ; tempNumber != 0; i++, tempNumber/=10) {
      strg[length-1-i] = ('0' + (tempNumber % 10)); 
   }
   
   strg[length] = '\0';
   
   if(isNegative)
      strg[0] = '-';
   
   return strg;
}

String::String() {
   _size = 0;
   _str = new char[_size+1];
   _str[0]= '\0';
}

String::String(const char* cs) {
   _size = strlen(cs);
   _str = new char[_size+1];
   strcpy(_str,cs);
}

String::String(const String& s) {
   _str = new char[s._size+1];
   _size = s._size;
   *this = s;
}

String::String(const char c) {
   _size = 1;
   _str = new char[_size+1];
   _str[0] = c;
   _str[_size] = '\0';
}

String::String(const int i) {
   _str = to_charArray(i);
   _size = strlen(_str);
}

String::String(const bool b) {
   _size = b ? strlen("true") : strlen("false");
   
   _str = new char[_size+1];
   
   strcpy(_str, b?"true":"false");
   _str[_size] = '\0';
}

String::~String() {
   delete[] _str;
}

const int String::size() const {
   return _size;
}

const char* String::c_str() const {
   return _str;
}

char& String::at(size_t pos) throw(std::runtime_error){
   if(pos >= _size || pos < 0)
      throw std::runtime_error("Out of range.");
   return _str[pos];
}

const char& String::at(size_t pos) const throw(std::runtime_error){
   if(pos >= _size || pos < 0)
      throw std::runtime_error("Out of range.");
   return _str[pos];
}

bool String::isEqual(const char* charArray) const {
   return !strcmp(_str, charArray);
}
bool String::isEqual(const String& s) const {
   return !strcmp(_str, s._str);
}
String& String::assign(const char* charArray) {
   if(_size != strlen(charArray)) {
      _size = strlen(charArray);
      delete[] _str;
      _str = new char[_size];
   }
   
   strcpy(_str, charArray);
   return *this;  
}

String& String::assign(const String& s) {
   if(_size != s._size) {
      _size = s._size;
      delete[] _str;
      _str = new char[_size];
   }
   
   strcpy(_str, s._str);
   return *this;
}

String& String::append(const char* charArray) {
   char* temp = new char[_size+strlen(charArray)+1];
   strcpy(temp, _str);
   strcpy(temp+_size, charArray);
   
   delete[] _str;
   _str = temp;
   _size += strlen(charArray);  
   
   _str[_size] = '\0';
   
   return *this;
}

String& String::append(const String& s) {
   char* temp = new char[_size+s._size+1];
   strcpy(temp, _str);
   strcpy(temp+_size, s._str);
   
   delete[] _str;
   _str = temp;
   _size += s._size;
   
   _str[_size] = '\0';
   
   return *this;
}

bool String::operator==(const char* charArray) const{
   return isEqual(charArray);
}

bool String::operator==(const String& s) const{
   return isEqual(s);
}

String& String::operator=(const String& s) {
   return assign(s);   
}

String String::operator+(const String& s) const{
   String newString(*this);
   newString.append(s);
   return newString;
}

String& String::operator+=(const String& s) {
   return append(s);   
}

String& String::between(int start, int end) const throw(std::runtime_error){
   if(start > end || start < 0 || end < 0 || end >= _size)
      throw std::runtime_error("Invalid range.");
   
   if(start == end)
      return *(new String());
   
   String* temp = new String();
   
   delete[] temp->_str;
   
   temp->_str = new char[end-start+1];
   
   strncpy(temp->_str, _str+start, end-start);
   temp->_str[end-start] = '\0';
   return *temp;
}      
   
std::ostream& operator<<(std::ostream& os, const String& s) {
   return os << s._str;
}