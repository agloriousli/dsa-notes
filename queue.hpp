#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.cpp"  // Assuming List template class exists

template <typename T> 
struct Queue: public List<T> { 
   // Queue based on linked list - inherits all list operations
   
   void enqueue( const T & e ) { 
      insertLast( e ); 
   } // Enqueue: insert element at rear
   
   T dequeue() { 
      return remove( first() ); 
   } // Dequeue: remove and return front element
   
   T & front() { 
      return first()->data; 
   } // Front: access front element
   
   // Utility methods for queue status
   bool empty() const {
      return List<T>::empty(); // Check if queue is empty
   }
   
   Rank size() const {
      return List<T>::size(); // Return number of elements
   }
   
   T & rear() {
      return last()->data;
   } // Rear: access rear element
}; 

#endif // QUEUE_HPP