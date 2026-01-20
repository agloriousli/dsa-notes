#include <bits/stdc++.h>
using namespace std;
typedef uint64_t Rank;

template <typename T>
class Vector {
private:
    T* _elem;
    Rank _capacity; //容量 // capacity
    Rank _size;

protected:
    void copy( const T* A, Rank lo, Rank hi );
    void expand( Rank d = 1 );
    
public:
    T& operator[]( Rank r );
    const T& operator[]( Rank r ) const;
    Vector( Rank c = DEFAULT_CAPACITY );
    Vector( Rank c, Rank s, T v );
    Vector( const T* A, Rank lo, Rank hi );
    Vector( Vector<T> const& V, Rank lo, Rank hi );
    Vector( T const* A, Rank lo, Rank hi );
    ~Vector();
    Vector<T>& operator=( Vector<T> const& V );
    void insert( Rank r, const T* A, Rank lo, Rank hi );
    T remove( Rank r );
    Rank find( const T& e, Rank lo, Rank hi ) const;
    Rank search( const T& e ) const;
    Rank search( const T& e, Rank lo, Rank hi ) const;
    Rank dedup();
    template <typename VST> void traverse( VST& visit );
    void uniquify();
};

template <typename T>
// Time Complexity: O(1) - Direct array access by index
T& Vector<T>::operator[]( Rank r ) { return _elem[ r ]; }

template <typename T>
// Time Complexity: O(1) - Direct array access by index
const T& Vector<T>::operator[]( Rank r ) const { return _elem[ r ]; }

template <typename T>
// Constructor: Initialize vector with given capacity
// Time Complexity: O(c) - Allocates array of size c
Vector<T>::Vector( Rank c ) //开辟空间，并按默认方法构造每一个成员对象 // allocate space and default-construct elements
{
    _elem = new T[ _capacity = c ];
    _size = 0;
}

template <typename T>
// Constructor: Initialize vector with capacity c, size s, all elements set to v
// Time Complexity: O(s) - Initializes s elements
Vector<T>::Vector( Rank c, Rank s, T v ) : Vector( c ) //s <= c：创建一个容量为c、规模为s // s <= c: create vector with capacity c and size s
{
    for ( _size = 0; _size < s; _elem[ _size++ ] = v );
} //所有元素均为v的向量 // all elements initialized to v

template <typename T>
// Constructor: Create vector by copying elements from A[lo, hi)
// Time Complexity: O(hi - lo) - Copies hi - lo elements
Vector<T>::Vector( const T* A, Rank lo, Rank hi ) { copy( A, lo, hi ); } //通过复制来创建 // create by copying

template <typename T>
// Copy Constructor: Create vector from another vector's range [lo, hi)
// Time Complexity: O(hi - lo) - Copies elements from source range
Vector<T>::Vector( Vector<T> const& V, Rank lo, Rank hi ) { copy( V._elem, lo, hi ); }

template <typename T>
// Constructor: Create vector from array A[lo, hi) with capacity doubled
// Time Complexity: O(hi - lo) - Copies elements with pre-doubled capacity
Vector<T>::Vector( T const* A, Rank lo, Rank hi ) : Vector( (hi - lo) * 2 ) { copy( A, lo, hi ); }

template <typename T>
// Destructor: Release allocated memory
// Time Complexity: O(1) - Just deallocates array pointer
Vector<T>::~Vector() { delete[] _elem; }

template <typename T>
// Protected method: Copy elements from array A[lo, hi) into internal buffer starting at index 0
// Time Complexity: O(hi - lo) - Copies all elements in range
void Vector<T>::copy( const T* A, Rank lo, Rank hi ) {
    for ( _size = 0; lo < hi; _size++, lo++ ) //A[lo,hi)复制至_elem[0,hi-lo) // copy A[lo,hi) to _elem[0,hi-lo)
        _elem[ _size ] = A[ lo ]; //T若非基本类型，则需重载操作符'='以实现深复制 // overload '=' for deep copy if T is non-primitive
}

template <typename T>
// Assignment Operator: Copy another vector into this one
// Time Complexity: O(n) - where n is size of source vector; may trigger expansion O(n) + copy O(n)
Vector<T>& Vector<T>::operator=( Vector<T> const& V ) {
    _size = 0; //删除原有内容 // clear existing content
    expand( V._size );
    copy( V._elem, 0, V._size ); // 107 整体复制 // copy all elements
    return *this; //返回当前向量的引用，以便链式赋值 // allow chained assignment
}

template <typename T>
// Insert d elements from A[lo, hi) at position r
// Shifts elements at [r, _size) to the right and inserts new elements
// Time Complexity: O(n - r + d) where n is current size; shifting is O(n - r), then copying O(d)
void Vector<T>::insert( Rank r, const T* A, Rank lo, Rank hi ) {
    Rank d = hi - lo;
    expand( d ); //若必要，先扩容：确保足以新增d个元素 // expand if necessary for d new elements
    for ( Rank i = _size - 1; i != r - 1; i-- ) _elem[ i + d ] = _elem[ i ]; //长度为n-r的后缀：后移 // shift suffix right
    while ( lo < hi ) _elem[ r++ ] = A[ lo++ ];
    _size += d; //插入d个元素 // inserted d elements
}

template <typename T>
// Remove element at position r and return its value
// Time Complexity: O(n - r) where n is current size - removes one element, shifts remaining
T Vector<T>::remove( Rank r ) {
    T e = _elem[ r ];
    remove( r, r + 1 );
    return e;
}

template <typename T>
// Protected method: Expand capacity if needed to accommodate d more elements
// Doubles capacity when expansion is necessary
// Time Complexity: O(n) amortized; O(1) when no expansion needed, O(n) when expansion required
void Vector<T>::expand( Rank d = 1 ) {
    if ( _size + d <= _capacity ) return; //若足以新增d个元素，则无需扩容 // no expansion needed if capacity suffices
    T* oldElem = _elem; //记下原数据区 // remember old buffer
    _capacity = ( _size + d ) * 2; //容量加倍 // double capacity
    _elem = new T[ _capacity ]; //分配新空间 // allocate new space
    copy( oldElem, 0, _size ); //转移数据 // move data
    delete[] oldElem; //释放原空间 // free old space
}

template <typename T>
// Search for element e in entire vector using optimal search algorithm
// Delegates to range search [0, _size)
// Time Complexity: O(log n) - logarithmic search via binary or Fibonacci search
Rank Vector<T>::search( const T& e ) const {
    return search( e, 0, _size ); //整体查找
}

template <typename T>
// Range search: Find element e in range [lo, hi)
// Randomly chooses between binary search and Fibonacci search for testing
// Time Complexity: O(log n) - logarithmic for both binary and Fibonacci search
Rank Vector<T>::search( const T& e, Rank lo, Rank hi ) const {
    return ( rand() % 2 ) ?
        binSearch( _elem, e, lo, hi ) :  //区间查找：二分查找算法 // binary search algorithm
        fibSearch( _elem, e, lo, hi ) ;  //Fibonacci查找算法 // Fibonacci search algorithm
}

template <typename K, typename V>
// Entry template: Key-value pair for dictionary/map like operations
// Supports comparison operators based on key field
// Time Complexity: All constructors and operators are O(1)
struct Entry { //词条模板类 // entry template class
    K key;
    V value; //关键码、数值 // key and value
    Entry( K k = K(), V v = V() ) : key( k ), value( v ) {};
    Entry( Entry<K, V> const& e ) : key( e.key ), value( e.value ) {}; //克隆 // 被判为相等的词条，未必相同 // clone; equal entries may differ
    bool operator==( Entry<K, V> const& e ) { return key == e.key; } //等于 // equal
    bool operator!=( Entry<K, V> const& e ) { return key != e.key; } //不等于 // thanks to comparator/equality, key and entry can be treated alike
    bool operator<( Entry<K, V> const& e ) { return key < e.key; } //小于 // less than
    bool operator>( Entry<K, V> const& e ) { return key > e.key; } //大于 // greater than
};

template <typename T>
// Find element e in range [lo, hi) using backward linear search
// Returns position of last match, or lo-1 if not found (UINT_MAX when lo=0)
// Time Complexity: O(hi - lo) worst case - linear search of range
Rank Vector<T>::find( const T& e, Rank lo, Rank hi ) const { //O(hi-lo) // linear search in [lo, hi)
    while ( ( lo < hi-- ) && ( e != _elem[ hi ] ) ); //从后向前，逐个比对 // scan backward
    return hi; //最靠后的命中者，或lo-1示意失败（lo==0时为-1 == UINT_MAX） // last hit or lo-1 (UINT_MAX) on failure
} //find

template <typename T>
// Remove all duplicate elements (keep only first occurrence of each value)
// Scans from index 1, checking if each element already exists in [0, i)
// Time Complexity: O(n^2) worst case - for each of n elements, searches previous elements O(n)
Rank Vector<T>::dedup() {
    //剔除相等的元素 // remove duplicates
    for ( Rank i = 1; i < _size; )
        if ( -1 == find( _elem[ i ], 0, i ) )
            i++; //O(i) // advance if unique so far
        else
            remove( i ); //O(n-i) // remove duplicate
} //O(n^2 124 // overall O(n^2)

template <typename T>
// Traverse all elements and apply functor/visitor to each
// Generic method to iterate through vector with custom operation
// Time Complexity: O(n) - visits each of n elements once; actual cost depends on visitor operation
template <typename VST>
void Vector<T>::traverse( VST& visit ) {
    for ( Rank i = 0; i < _size; i++ ) visit( _elem[ i ] );
}

template <typename T>
// Cumulate functor: Accumulates sum of vector elements
// Used with traverse() to calculate total of all elements
// Time Complexity: O(1) per element - single addition operation
struct Cumulate { //累计一个T类型对象的数值 // accumulate value of type T
    T& s;
    Cumulate( T& sum ) : s( sum ) {}
    virtual void operator()( T& e ) { s += e; } //约定T可直接相加 // assumes T supports addition
}; //Cumulate

template <typename T>
// Calculate sum of all elements in vector
// Uses traverse with Cumulate functor
// Time Complexity: O(n) - sums all n elements
T sum( Vector<T>& V ) { //统计向量中所有元素的总和 // sum all elements
    T sum = 0;
    V.traverse( Cumulate<T>( sum ) ); //以Cumulate为基本操作进行遍历 // traverse with Cumulate functor
    return sum; //返回总和 // return total
}

template <typename T>
// Compare functor: Counts adjacent inversions (pairs where pred > current)
// Maintains predecessor value and increments counter when inversion found
// Time Complexity: O(1) per element - single comparison and assignment
struct Compare { //判断线性序列中的一个元素是否与其前驱顺序 // compare with predecessor to count inversions
    T pred;
    int& i; //前驱、（相邻）逆序对的计数器 // counter for adjacent inversions
    Compare( int& invs, T& first ) : pred( first ), i( invs ) {}
    virtual void operator()( T& e ) {
        i += ( pred > e );
        pred = e;
    }
}; //Compare

template <typename T>
// Count total adjacent inversions in vector
// An inversion is a pair of adjacent elements where left > right
// Returns 0 if vector is sorted in ascending order
// Time Complexity: O(n) - single pass through vector comparing adjacent elements
int inv( Vector<T>& V ) { //统计向量中相邻逆序对的总数 // count adjacent inversions
    int invs = 0;
    V.traverse( Compare<T>( invs, V[ 0 ] ) ); //以Compare为基本操作做遍历 // traverse using Compare functor
    return invs; //返回逆序对总数：为零当且仅当向量整体有序 // zero iff fully ordered
} //inv

template <typename T>
// Remove consecutive duplicate elements from sorted vector
// First overload: Removes duplicate at position i if found in [0, i)
// Time Complexity: O(n^2) worst case - each element searches backward O(n), possible removal for each
void Vector<T>::uniquify() {
    for ( Rank i = 1; i < _size; ) //从前向后，逐一比对相邻的[i-1]和[i] // scan forward comparing neighbors
        if ( _elem[ i - 1 ] != _elem[ i ] )
            i++; //若不等，则转至下一对元素 // move to next pair when different
        else
            remove( i ); //否则，删除居后者 // remove trailing duplicate
}

template <typename T>
// Remove all duplicate elements efficiently by consolidating unique values
// Second overload: Moves unique elements to front, shrinks size
// Assumes vector is sorted; consolidates consecutive duplicates into one
// Time Complexity: O(n) - single pass through vector; only copies unique values
void Vector<T>::uniquify() {
    Rank i = 0; //前缀[0,i]包含目前已知的所有无重元素 // prefix [0,i] holds unique elements
    for ( Rank j = 1; j < _size; j++ ) //逐一考查[j] // examine each j
        if ( _elem[ i ] != _elem[ j ] ) //不等，当且仅当[j]为一个区间的首元素 // different means new unique head
            _elem[ ++i ] = _elem[ j ]; //故将[j]归入无重的前缀 // place into unique prefix
    _size = ++i;
    shrink();
}

int main() {
    return 0;
}