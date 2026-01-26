#include <bits/stdc++.h>
#include <listnode.h>
using Rank = unsigned int; 
using namespace std;

template <typename T> struct ListNode;
template <typename T> using ListNodePosi = ListNode<T>*; // List node position
template <typename T> struct ListNode { // List node template class (implemented as doubly-linked list)
// Members
   T data; ListNodePosi<T> pred, succ; // Data, predecessor, successor
// Constructors
   ListNode() {} // Constructor for head and tail sentinels
   ListNode ( T const& e, ListNodePosi<T> p = NULL, ListNodePosi<T> s = NULL )
      : data( e ), pred( p ), succ( s ) {} // Default constructor (class T must define copy operator)
// Operations
   ListNodePosi<T> insertPred( T const& e ); // Insert new node immediately before current node
   ListNodePosi<T> insertSucc( T const& e ); // Insert new node immediately after current node
};

template <typename T> class List { // List template class

private:
   Rank _size; ListNodePosi<T> head, tail; // Size, head sentinel, tail sentinel

protected:
   void init(); // Initialize list upon creation
   Rank clear(); // Clear all nodes
   void copyNodes( ListNodePosi<T>, Rank ); // Copy n items starting from position p
   ListNodePosi<T> merge( ListNodePosi<T>, Rank, List<T>&, ListNodePosi<T>, Rank ); // Merge
   void mergeSort( ListNodePosi<T>&, Rank ); // Merge sort n consecutive nodes starting from p
   void selectionSort( ListNodePosi<T>, Rank ); // Selection sort n consecutive nodes starting from p
   void insertionSort( ListNodePosi<T>, Rank ); // Insertion sort n consecutive nodes starting from p
   void radixSort( ListNodePosi<T>, Rank ); // Radix sort n consecutive nodes starting from p

public:
// Constructors
   List() { init(); } // Default constructor
   List( List<T> const& L ); // Copy entire list L
   List( List<T> const& L, Rank r, Rank n ); // Copy n items starting from position r in list L
   List( ListNodePosi<T> p, Rank n ); // Copy n items starting from position p
   // Destructor
   ~List(); // Release all nodes (including head and tail sentinels)
// Read-only access interface
   Rank size() const { return _size; } // Size
   bool empty() const { return _size <= 0; } // Check if empty
   ListNodePosi<T> operator[]( Rank r ) const; // Overload, support rank-based access (low efficiency)
   ListNodePosi<T> first() const { return head->succ; } // Position of first node
   ListNodePosi<T> last() const { return tail->pred; } // Position of last node
   bool valid( ListNodePosi<T> p ) // Check if position p is valid for external use
   { return p && ( tail != p ) && ( head != p ); } // Treat head and tail sentinels as NULL
   ListNodePosi<T> find( T const& e ) const // Search in unordered list
   { return find( e, _size, tail ); }
   ListNodePosi<T> find( T const& e, Rank n, ListNodePosi<T> p ) const; // Search in unordered range
   ListNodePosi<T> search( T const& e ) const // Search in ordered list
   { return search( e, _size, tail ); }
   ListNodePosi<T> search( T const& e, Rank n, ListNodePosi<T> p ) const; // Search in ordered range
   ListNodePosi<T> selectMax( ListNodePosi<T> p, Rank n ); // Select maximum from p and its n-1 successors
   ListNodePosi<T> selectMax() { return selectMax( head->succ, _size ); } // Select overall maximum
// Writable access interface
   ListNodePosi<T> insertFirst( T const& e ); // Insert e as first node
   ListNodePosi<T> insertLast( T const& e ); // Insert e as last node
   ListNodePosi<T> insert( ListNodePosi<T> p, T const& e ); // Insert e as successor of p
   ListNodePosi<T> insert( T const& e, ListNodePosi<T> p ); // Insert e as predecessor of p
   T remove( ListNodePosi<T> p ); // Remove node at valid position p, return removed node
   void merge( List<T>& L ) { merge( head->succ, _size, L, L.head->succ, L._size ); } // Merge entire list
   void sort( ListNodePosi<T>, Rank ); // Sort list range
   void sort() { sort( first(), _size ); } // Sort entire list
   Rank dedup(); // Remove duplicates in unordered list
   Rank uniquify(); // Remove duplicates in ordered list
   void reverse(); // Reverse (reverse front and back)
// Traversal
   void traverse( void ( * )( T& ) ); // Apply visit operation sequentially (function pointer)
   template <typename VST> void traverse( VST& ); // Apply visit operation sequentially (functor)
}; // List

template <typename T> //O(r) time
T List<T>::operator[](Rank r) const {
    Posi(T) p = first();
    while(0 < r--) p = p -> succ; //the kth element is k-1 movements through linkedlist
    return p->data;
}


/*
列表 (list)
节点 (node)
前驱 (predecessor)
后驱 (successor)
首末 (first/last) node

*/