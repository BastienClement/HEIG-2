/* 
 * File:   List.h
 * Author: Bastien Clément & Alain Hardy
 * 
 * Goal: Implémentation d'une liste générique doublement chainée.
 *
 * Created on 17. avril 2016, 22:56
 */

#ifndef LIST_H
#define	LIST_H

#include <stdexcept>

template<typename T>
class List {

   class Element {
   public:
      Element(T o): data(o){};
      T data;
      Element* previous;
      Element* next;
   };
   Element* head;
   Element* tail;
   size_t _size;
   
public:
   
   class Iterator {
   public:
      Iterator(Element* o) {data = o;};

      /*
       * Opérateur de pré-incrémentation
       */
      Iterator& operator++() throw(const std::runtime_error&){
         if(data->next != nullptr)
            data = data->next;
         else
            throw std::runtime_error("Out of range");

         return *this;   
      }
      
      /*
       * Opérateur de post-incrémentation.
       */
      Iterator operator++(int) throw(const std::runtime_error&){
         List<T>::Iterator temp(data);
         if(data->next != nullptr)
            data = data->next;
         else
            throw std::runtime_error("Out of range");

         return temp;
      }
      
      /*
       * Opérateur de pré-décrémentation.
       */
      Iterator& operator--() throw(const std::runtime_error&){
         if(data->previous != nullptr)
            data = data->previous;
         else
            throw std::runtime_error("Out of range");

         return *this;
      }
      
      /*
       * Opérateur de post-decrémentation.
       */
      Iterator operator--(int) throw(const std::runtime_error&){
         List<T>::Iterator temp(data);
         if(data->previous != nullptr)
            data = data->previous;
         else
            throw std::runtime_error("Out of range");

         return temp;
      }

      /*
       * Retourne la valeur de l'élément sur lequel l'itérateur pointe.
       */
      T& operator*() {
         return data->data;
      }
      
      /*
       * Opérateur d'égalité.
       */
      bool operator==(const Iterator& it) {
         return this->data == it.data;
      }
      
      /*
       * Opérateur d'inégalité.
       */
      bool operator!=(const Iterator& it) {
         return !(this->data == it.data);        
      }
   private:      
      Element* data;
   };
   
   List(): head(nullptr), tail(nullptr), _size(0) {};
   
   List(const List& orig): List() {
      _size = orig._size;
      copy(orig);      
   }
   
   virtual ~List() {
      if(head == nullptr) return;
   
      while(head->next != nullptr) {
         head = head->next;
         delete head->previous;
      }
      delete head;
   }

   /*
    * Opérateur d'affectation.
    */
   List& operator=(const List& orig) {
      if(this != &orig) {
         copy(orig);
      }

      return *this;
   }
   
   /*
    * Retourne la valeur à un certain index de la liste.
    */
   T& operator[](int index) throw(const std::runtime_error&){
      if(index >= _size || index < 0)
         throw std::runtime_error("Out of range");

      Element *current = head;

      for(int i = 0; i < index; i++) {
         current = current->next;
      }

      return current->data;     
   }
   
   /*
    * Retourne la taille de la liste.
    */
   size_t size() const {
      return _size;
   }
   
   /*
    * Ajoute un élément en début de liste.
    */
   void insert(const T& o) {
      Element* e = new Element(o);
      e->next = head;
      e->previous = nullptr;
      head->previous = e; 
      head = e;
      if(tail == nullptr) 
         tail = e;
      _size++;
   }
   
   /*
    * Ajoute un élément en fin de liste.
    */
   void append(const T& o) {
      Element* e = new Element(o);
      e->next = nullptr;
      e->previous = nullptr;

      if(head == nullptr) {
         head = e;
      } else {
         if(tail != nullptr){
            tail->next = e;
            e->previous = tail;
         }
      }
      tail = e;
      _size++;      
   }
   
   /*
    * Supprime un élément par rapport à sa position dans liste.
    */
   void remove(int index) throw(const std::runtime_error&){
      if(index >= _size || size < 0) {
         throw std::runtime_error("Out of range.");
      }

      if(index == 0) {
         head = head->next;
         delete head->previous;
         head->previous = nullptr;         
      }
      else if(index == _size-1) {
         tail = tail->previous;
         delete tail->next;
         tail->next = nullptr;
      }
      else {         
         Element* current = head;
      
         for(int i = 0; i < index; i++, current = current->next);
         
         current->previous->next = current->next;
         current->next->previous = current->previous;
      }

      size--;
   }
   
   /*
    * Supprime la première occurence d'une élément.
    * Ne fais rien si aucune occurence de l'élément n'a été trouvée.
    */
   void remove(T o) {
      bool found = false;
      Element* current;
      for(current = head; current->next != nullptr && current->data != o; current = current->next) {
         if(current->data == o)
            found = true;;
      }
      
      if(found) {
         if(current->previous == nullptr) {
            head = current->next;
            head->previous = nullptr;
            delete current;
         }
         else if(current->next == nullptr) {
            current->previous->next = nullptr;
            delete current;
         }
         else {
            current->previous->next = current->next;
            current->next->previous = current->previous;
         }

         size--;
      }
   }
   
   /*
    * Retourne un itérateur sur le premier élément.
    */
   Iterator begin() {
      return Iterator(head);
   }
   
   /*
    * Retourne un itérateur sur le dernier élément.
    */
   Iterator end() {
      return Iterator(tail);
   }
   
   /*
    * Retroune un itérateur sur la première occurence d'une élément.
    * Renvoi un itérateur sur le dernier élément si rien n'as été trouvé.
    */
   Iterator find(T o) {
      Element* current;
      for(current = head; current != nullptr && current->data != o; current = current->next);
      return Iterator(current);      
   }
   
private:
   /*
    * Copie tous les éléments de orig dans l'instance de la liste.
    */
   void copy(const List& orig) {
      Element* current = orig.head;      
      
      while(current != nullptr) {
         this->append(current->data);
         current = current->next;
      }
   }      
};

#endif	/* LIST_H */

