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

template <typename T> void List<T>::init() { //初始化，创建列表对象时统一调用
   //Initialize a new list with head and tail as the only two nodes
   //Head has no predecessor, tail has no successor
head = new ListNode<T>;
tail = new ListNode<T>;
head->succ = tail; 
head->pred = NULL;
tail->pred = head; 
tail->succ = NULL;
_size = 0;
}

//nodeOne.movePred(nodetwo*) makes nodeOne the pred of nodeTwo 
template <typename T> void ListNode<T>::movePred(LNP<T> s){
   pred->succ = succ;
   succ->pred = pred;
   succ = s;
   s->pred = this;
}

//Coping in lists//;
template <typename T> 
List<T>::List( List<T> const & L ) { copy( L.first(), L._size ); }
template <typename T> 
List<T>::List( List<T> const & L, Rank r, Rank n ) { copy( L[r], n ); }
//Copying n nodes to a new list starting from node p
template <typename T> 
//List <T> newList;
//newList.copy(aNodeFromOldList*, n) 
void List<T>::copy(LNP<T> p, Rank n){
   for( init(); n--; p = p->succ)
      insertLast(p->data);
}

/*
This is a function of List that returns an LNP (a pointer to a node in the list)
This pointer points to the node that is r nodes after the first node
Pointer Arithmetic: since List has no particular order, we overload the + operator
*/
template <typename T> LNP<T> List<T>::operator[]( Rank r ) const
{ return *first() + r; } 

template <typename T> LNP<T> ListNode<T>::operator+( Rank r ){
for ( LNP<T> p = this; ; p = p->succ, r-- ) //从当前节点出发
/*
"this" is a pointer to current object
the + operator is applied to *first() and r
*/
if ( 0 == r ) return p; //顺数第r个节点即是目标节点
}

template <typename T> Rank ListNode<T>::operator-( LNP<T> h ) { //h<=this
/*
Returns how many nodes it takes to go from node h to the node its called on
nodeFive - nodeThree = 2
*/
for ( Rank n = 0; ; h = h->succ, n++ ) //区间内的节点，挨个报数
if ( h == this ) return n;

}


template <typename T> LNP<T> ListNode<T>::insertPred( const T & e ) {
LNP<T> x = new ListNode( e, pred, this ); //创建新节点（pred或为head）
pred->succ = x; pred = x; return x; //列表接纳新节点（操作次序不可颠倒)
}

template <typename T> T List<T>::remove( LNP<T> p ) {
T e = p->data;
p->pred->succ = p->succ;
p->succ->pred = p->pred;
delete p;
_size--;
return e;
}

//Destructor: Delete all nodes including sentinels (Also O(n) time)
template <typename T>
List<T>::~List() {
for ( LNP<T> x = head;  // Start from head sentinel
x != tail;              // Continue until we reach tail
delete (x = x->succ)->pred );  // Advance x forward, then delete the node behind it
                               // (x = x->succ) moves x to next node
                               // ->pred accesses predecessor of new x (the old x)
                               // delete removes that old node
delete tail;            // Finally delete tail sentinel after loop ends
}

template <typename T> LNP<T> //在无序列表区间(h,t)内，找到等于e的最后者
List<T>::find( LNP<T> h, const T & e, LNP<T> t ) const { //h < t
while ( h != (t = t->pred) ) //自后向前
if ( e == t->data ) //逐个比对（假定类型T已重载“==”）
return t; //直至命中
return NULL; //或失败
} //find：O(n)

template <typename T>
LNP<T> find( const T & e ) const { return find( head, e, tail ); }

template <typename T> void List<T>::dedup() { //O(n^2)
for ( LNP<T> p = first(); p != tail; p = p->succ ) //O(n)
if ( LNP<T> q = find( head, p->data, p ) ) //O(n)
remove ( q ); //O(1)
}


template <typename T> struct Cumulate { //累计一个T类型对象的数值
T & s;
Cumulate( T & sum ) : s( sum ) {}
virtual void operator() ( T & e ) { s += e; } //约定T可直接相加
}; //Cumulate

template <typename T> T sum( List<T> & L ) { //统计列表中所有元素的总和
T sum = 0;
L.traverse( Cumulate<T>( sum ) ); //以Cumulate为基本操作进行遍历
return sum; //返回总和
} 


template <typename T> struct Compare { //判断线性序列中的一个元素是否与其前驱顺序
T pred; int & inv; //前驱、（相邻）逆序对的计数器
Compare( int & inversions, T & first ) : pred( first ), inv( inversions ) {}
virtual void operator() ( T & e ) { //Functor
   inv += ( pred > e ); pred = e; 
   }
}; //Compare

template <typename T> int inv( List<T> & L ) { //判断列表是否整体有序
int inversions = 0;
L.traverse( Compare<T>( inversions, L[0]->data ) ); //以Compare为基本操作做遍历
return inversions; //返回总数
}

/*
Functors:
1. Create an object of Cumulate
int total = 0;
Cumulate<int> accumulator(total);  // s references total

// Call it like a function:
int x = 5;
accumulator(x);  // Calls accumulator.operator()(x)
// total now = 5
*/
/*
列表 (list)
节点 (node)
前驱 (predecessor)
后驱 (successor)
首末 (first/last) node

*/