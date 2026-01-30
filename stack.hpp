#ifndef STACK_HPP
#define STACK_HPP
#include "vector.cpp" 

template <typename T> 
struct Stack: public Vector<T> {
   // All stack operations below require O(1) amortized time
   
   void push( const T& e ) { 
      insert( e ); 
   } // Push: insert element at the end
   
   T pop() { 
      return remove( Vector<T>::_size - 1 ); 
   } // Pop: remove and return top element
   
   T& top() { 
      return Vector<T>::_elem[ Vector<T>::_size - 1 ]; 
   } // Top: access the top element without removing
   
   bool empty() const {
      return Vector<T>::_size == 0; // Check if stack is empty
   }
   
   Rank size() const {
      return Vector<T>::_size; // Return number of elements
   }
}; 

#endif 