/**
 * COMPLETE VECTOR IMPLEMENTATION IN C++ WITH ENGLISH EXPLANATIONS
 * Based on Tsinghua University Data Structures & Algorithms Course Material
 * 
 * This file demonstrates:
 * 1. How vectors work internally
 * 2. Template classes for generic programming
 * 3. Dynamic array management
 * 4. Operator overloading
 * 5. Memory management and optimization
 */

#include <iostream>
#include <algorithm>  // For copy and other algorithms
#include <stdexcept>  // For exceptions
using namespace std;

// ============================================================
// PART 1: BASIC DEFINITIONS AND SETUP
// ============================================================

// Rank is just an integer type used for indexing
typedef int Rank;

// Default capacity for new vectors (small for testing)
#define DEFAULT_CAPACITY 2

// ============================================================
// PART 2: VECTOR TEMPLATE CLASS DEFINITION
// ============================================================

/**
 * Vector<T> - A dynamic array template class
 * 
 * This is similar to std::vector but implemented from scratch
 * to demonstrate how dynamic arrays work internally.
 * 
 * Key features:
 * - Dynamic resizing (grows as needed)
 * - Random access via operator[]
 * - Automatic memory management
 * - Template works with any data type
 */
template <typename T>
class Vector {
private:
    // ============ PRIVATE MEMBER VARIABLES ============
    
    /**
     * _elem - Pointer to the dynamic array (data storage)
     * 
     * This is NOT the array itself, but a pointer to the first element.
     * The actual array is allocated on the heap with 'new'.
     * 
     * Example: If T = int, then _elem is of type int*
     * It points to: [int][int][int]... on the heap
     */
    T* _elem;
    
    /**
     * _capacity - Total number of elements that can be stored
     * 
     * This is the size of the allocated array on the heap.
     * When we need more space, we allocate a larger array.
     */
    Rank _capacity;
    
    /**
     * _size - Number of elements actually stored
     * 
     * This is always <= _capacity.
     * _size tells us how many elements are currently in use.
     */
    Rank _size;
    
protected:
    // ============ PROTECTED INTERNAL METHODS ============
    
    /**
     * copy() - Internal method to copy elements from a source array
     * 
     * Copies elements A[lo] to A[hi-1] into this vector.
     * This is used by constructors and the assignment operator.
     * 
     * @param A   Pointer to source array
     * @param lo  Starting index (inclusive)
     * @param hi  Ending index (exclusive)
     */
    void copy(const T* A, Rank lo, Rank hi) {
        // Allocate new array with double the needed space
        // This provides room for future growth
        _elem = new T[_capacity = 2 * (hi - lo)];
        _size = 0;
        
        // Copy elements one by one
        while (lo < hi) {
            _elem[_size] = A[lo];  // Copy element
            _size++;                // Increment size
            lo++;                   // Move to next source element
        }
    }
    
    /**
     * expand() - Internal method to increase capacity when full
     * 
     * When _size reaches _capacity, we need more space.
     * This method:
     * 1. Allocates a new, larger array (usually double the size)
     * 2. Copies all elements from old array to new array
     * 3. Deletes the old array
     * 4. Updates _elem to point to the new array
     */
    void expand() {
        // If there's still space, no expansion needed
        if (_size < _capacity) return;
        
        // Save pointer to old array
        T* oldElem = _elem;
        
        // Double the capacity (or set to DEFAULT_CAPACITY if currently 0)
        _capacity = max(_capacity, DEFAULT_CAPACITY) * 2;
        _elem = new T[_capacity];  // Allocate new larger array
        
        // Copy all elements from old array to new array
        for (Rank i = 0; i < _size; i++) {
            _elem[i] = oldElem[i];  // Copy element by element
        }
        
        // Free the memory of the old array
        delete[] oldElem;
    }
    
    /**
     * shrink() - Internal method to reduce capacity when underutilized
     * 
     * If the vector is using much less space than allocated,
     * we can save memory by shrinking the array.
     * (Not shown in original but important for completeness)
     */
    void shrink() {
        // Only shrink if capacity is much larger than size
        // and capacity is greater than minimum
        if (_capacity <= DEFAULT_CAPACITY) return;
        if (_size * 4 > _capacity) return;  // Still using >25% capacity
        
        // Halve the capacity
        T* oldElem = _elem;
        _capacity /= 2;
        _elem = new T[_capacity];
        
        // Copy elements
        for (Rank i = 0; i < _size; i++) {
            _elem[i] = oldElem[i];
        }
        
        delete[] oldElem;
    }
    
public:
    // ============ CONSTRUCTORS ============
    
    /**
     * Constructor 1: Default constructor
     * 
     * Creates an empty vector with default capacity.
     * 
     * @param c Initial capacity (defaults to DEFAULT_CAPACITY)
     */
    Vector(Rank c = DEFAULT_CAPACITY) {
        _elem = new T[_capacity = c];  // Allocate array on heap
        _size = 0;                     // Initially empty
        cout << "Default constructor: capacity = " << _capacity << endl;
    }
    
    /**
     * Constructor 2: Create vector with size s, all elements = v
     * 
     * Creates a vector with capacity c, containing s copies of value v.
     * 
     * @param c Capacity (allocated memory)
     * @param s Size (number of elements)
     * @param v Value to fill the vector with
     */
    Vector(Rank c, Rank s, T v) : Vector(c) {  // Delegate to constructor 1
        for (_size = 0; _size < s; _elem[_size++] = v);  // Fill with v
        cout << "Fill constructor: size = " << _size 
             << ", all elements = " << v << endl;
    }
    
    /**
     * Constructor 3: Copy from array range A[lo, hi)
     * 
     * Creates a vector by copying elements from an existing array.
     * 
     * @param A  Pointer to source array
     * @param lo Starting index (inclusive)
     * @param hi Ending index (exclusive)
     */
    Vector(const T* A, Rank lo, Rank hi) {
        copy(A, lo, hi);  // Use internal copy method
        cout << "Array copy constructor: copied " << _size 
             << " elements from array" << endl;
    }
    
    /**
     * Constructor 4: Copy from another vector range V[lo, hi)
     * 
     * Creates a vector by copying elements from another vector.
     * 
     * @param V  Source vector
     * @param lo Starting index (inclusive)
     * @param hi Ending index (exclusive)
     */
    Vector(const Vector<T>& V, Rank lo, Rank hi) {
        copy(V._elem, lo, hi);  // Copy from vector's internal array
        cout << "Vector range copy constructor: copied " 
             << _size << " elements" << endl;
    }
    
    /**
     * Constructor 5: Copy constructor (entire vector)
     * 
     * Creates a new vector that's a copy of an existing vector.
     * This is a DEEP COPY - new array is allocated.
     * 
     * @param V Vector to copy from
     */
    Vector(const Vector<T>& V) {
        copy(V._elem, 0, V._size);  // Copy entire vector
        cout << "Copy constructor: deep copied " << _size << " elements" << endl;
    }
    
    // ============ DESTRUCTOR ============
    
    /**
     * Destructor - Cleans up allocated memory
     * 
     * Automatically called when vector goes out of scope.
     * MUST delete[] the array to avoid memory leak.
     */
    ~Vector() {
        delete[] _elem;  // Free the heap-allocated array
        cout << "Destructor: freed array of " << _capacity << " elements" << endl;
    }
    
    // ============ OPERATOR OVERLOADING ============
    
    /**
     * operator[] - Subscript operator for array-like access
     * 
     * Allows accessing elements using V[r] syntax, just like arrays.
     * 
     * TWO VERSIONS:
     * 1. Non-const version (returns T&): Can modify element
     * 2. Const version (returns const T&): Read-only access
     * 
     * Example usage:
     * V[2] = 100;      // Uses non-const version
     * int x = V[2];    // Can use either
     * const Vector& cv = V;
     * int y = cv[2];   // Uses const version
     */
    
    // Non-const version: can be used as LEFT value (for modification)
    T& operator[](Rank r) {
        // Check bounds (simplified - production code should throw exception)
        if (r < 0 || r >= _size) {
            throw out_of_range("Vector index out of bounds");
        }
        return _elem[r];  // Return REFERENCE to element (can modify)
    }
    
    // Const version: can only be used as RIGHT value (read-only)
    const T& operator[](Rank r) const {
        if (r < 0 || r >= _size) {
            throw out_of_range("Vector index out of bounds");
        }
        return _elem[r];  // Return CONST reference (cannot modify)
    }
    
    /**
     * operator= - Assignment operator (DEEP COPY)
     * 
     * Copies one vector to another. Creates a new array and copies all elements.
     * Returns reference to allow chained assignment: a = b = c;
     * 
     * IMPORTANT: Must handle self-assignment (a = a) correctly!
     * 
     * @param V Vector to copy from
     * @return Reference to this vector (for chaining)
     */
    Vector<T>& operator=(const Vector<T>& V) {
        cout << "Assignment operator called" << endl;
        
        // Check for self-assignment (a = a)
        if (this == &V) {
            cout << "  (Self-assignment, nothing to do)" << endl;
            return *this;
        }
        
        // Delete old array to avoid memory leak
        delete[] _elem;
        
        // Allocate new array with appropriate capacity
        // We use V._size * 2 to allow future growth (like in copy())
        _capacity = 2 * V._size;
        _elem = new T[_capacity];
        _size = V._size;
        
        // Copy all elements
        for (Rank i = 0; i < _size; i++) {
            _elem[i] = V._elem[i];
        }
        
        cout << "  Copied " << _size << " elements (deep copy)" << endl;
        return *this;  // Return reference for chaining
    }
    
    // ============ PUBLIC INTERFACE METHODS ============
    
    /**
     * size() - Get number of elements in vector
     * 
     * @return Current size (number of elements)
     */
    Rank size() const { return _size; }
    
    /**
     * empty() - Check if vector is empty
     * 
     * @return true if size == 0, false otherwise
     */
    bool empty() const { return _size == 0; }
    
    /**
     * capacity() - Get total capacity of vector
     * 
     * @return Current capacity (allocated memory size)
     */
    Rank capacity() const { return _capacity; }
    
    /**
     * insert() - Insert element at position r
     * 
     * Inserts element e at index r. All elements from r to end
     * are shifted one position to the right.
     * 
     * @param r Position to insert at (0 <= r <= _size)
     * @param e Element to insert
     * @return Position where inserted (r)
     */
    Rank insert(Rank r, const T& e) {
        // Check if we need more space
        expand();
        
        // Shift elements to the right to make space
        for (Rank i = _size; i > r; i--) {
            _elem[i] = _elem[i - 1];
        }
        
        // Insert new element
        _elem[r] = e;
        _size++;
        
        return r;
    }
    
    /**
     * push_back() - Add element at the end
     * 
     * Convenience method equivalent to insert(_size, e)
     * 
     * @param e Element to add
     * @return Position where inserted (_size - 1)
     */
    Rank push_back(const T& e) {
        return insert(_size, e);
    }
    
    /**
     * remove() - Remove element at position r
     * 
     * Removes element at index r. All elements after r
     * are shifted one position to the left.
     * 
     * @param r Position to remove (0 <= r < _size)
     * @return The removed element
     */
    T remove(Rank r) {
        // Save element to return
        T e = _elem[r];
        
        // Shift elements to the left to fill the gap
        for (Rank i = r; i < _size - 1; i++) {
            _elem[i] = _elem[i + 1];
        }
        
        _size--;
        
        // Optional: shrink if too empty
        shrink();
        
        return e;
    }
    
    /**
     * find() - Search for element in unsorted vector
     * 
     * Linear search from position lo to hi-1.
     * Returns position if found, hi if not found.
     * 
     * @param e Element to search for
     * @param lo Starting position (inclusive)
     * @param hi Ending position (exclusive)
     * @return Position of element, or hi if not found
     */
    Rank find(const T& e, Rank lo, Rank hi) const {
        while (lo < hi && _elem[lo] != e) {
            lo++;
        }
        return lo;  // Returns hi if not found
    }
    
    /**
     * find() - Search in entire vector
     * 
     * @param e Element to search for
     * @return Position of element, or size() if not found
     */
    Rank find(const T& e) const {
        return find(e, 0, _size);
    }
    
    /**
     * sort() - Sort the vector (simple bubble sort for demonstration)
     * 
     * Sorts elements in range [lo, hi) in ascending order.
     * In production, you'd use a better algorithm.
     * 
     * @param lo Starting position
     * @param hi Ending position
     */
    void sort(Rank lo, Rank hi) {
        // Simple bubble sort for demonstration
        for (Rank i = lo; i < hi - 1; i++) {
            for (Rank j = lo; j < hi - i - 1 + lo; j++) {
                if (_elem[j] > _elem[j + 1]) {
                    // Swap elements
                    T temp = _elem[j];
                    _elem[j] = _elem[j + 1];
                    _elem[j + 1] = temp;
                }
            }
        }
    }
    
    /**
     * sort() - Sort entire vector
     */
    void sort() {
        sort(0, _size);
    }
    
    /**
     * display() - Print vector contents
     * 
     * Shows elements, size, and capacity for debugging.
     * 
     * @param name Optional name for the vector
     */
    void display(const char* name = "Vector") const {
        cout << name << ": [";
        for (Rank i = 0; i < _size; i++) {
            cout << _elem[i];
            if (i < _size - 1) cout << ", ";
        }
        cout << "]" << endl;
        cout << "  Size: " << _size << ", Capacity: " << _capacity 
             << ", Address: " << _elem << endl;
    }
};

// ============================================================
// PART 3: DEMONSTRATION PROGRAM
// ============================================================

int main() {
    cout << "=== VECTOR IMPLEMENTATION DEMONSTRATION ===\n" << endl;
    
    cout << "1. CREATING VECTORS WITH DIFFERENT CONSTRUCTORS:" << endl;
    cout << "================================================" << endl;
    
    // Default constructor
    Vector<int> v1;
    v1.display("v1 (default)");
    
    // Fill constructor: 5 elements, all with value 100
    Vector<int> v2(10, 5, 100);
    v2.display("v2 (fill)");
    
    // Copy constructor
    Vector<int> v3(v2);
    v3.display("v3 (copy of v2)");
    
    cout << "\n2. ARRAY-LIKE ACCESS WITH operator[]:" << endl;
    cout << "=====================================" << endl;
    
    // Create a vector and fill it
    Vector<char> chars;
    chars.push_back('D');
    chars.push_back('A');
    chars.push_back('T');
    chars.push_back('A');
    chars.display("chars");
    
    // Access elements like an array
    cout << "chars[0] = " << chars[0] << endl;
    cout << "chars[2] = " << chars[2] << endl;
    
    // Modify elements
    chars[1] = 'E';
    cout << "After chars[1] = 'E': ";
    chars.display("chars");
    
    // Const access
    const Vector<char>& constRef = chars;
    cout << "constRef[3] = " << constRef[3] << " (read-only)" << endl;
    // constRef[3] = 'X';  // Would cause compilation error
    
    cout << "\n3. INSERT AND REMOVE OPERATIONS:" << endl;
    cout << "=================================" << endl;
    
    Vector<string> words;
    words.push_back("Hello");
    words.push_back("World");
    words.display("words");
    
    // Insert at position 1
    words.insert(1, "Beautiful");
    words.display("words after insert(1, 'Beautiful')");
    
    // Remove element at position 0
    string removed = words.remove(0);
    cout << "Removed: \"" << removed << "\"" << endl;
    words.display("words after remove(0)");
    
    cout << "\n4. ASSIGNMENT OPERATOR (DEEP COPY):" << endl;
    cout << "===================================" << endl;
    
    Vector<int> a(5, 3, 10);  // [10, 10, 10]
    Vector<int> b(3, 2, 20);  // [20, 20]
    
    a.display("a before assignment");
    b.display("b before assignment");
    
    // Assignment operator (deep copy)
    a = b;
    
    a.display("a after a = b");
    b.display("b after a = b (unchanged)");
    
    // Modify a to show they're independent
    a[0] = 999;
    cout << "After a[0] = 999:" << endl;
    a.display("a");
    b.display("b (still unchanged)");
    
    // Self-assignment test
    a = a;
    a.display("a after self-assignment");
    
    cout << "\n5. FIND OPERATION:" << endl;
    cout << "===================" << endl;
    
    Vector<int> numbers;
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    numbers.push_back(20);
    numbers.push_back(40);
    numbers.display("numbers");
    
    int searchFor = 20;
    Rank pos = numbers.find(searchFor);
    if (pos < numbers.size()) {
        cout << "Found " << searchFor << " at position " << pos << endl;
    } else {
        cout << searchFor << " not found" << endl;
    }
    
    // Find second occurrence
    pos = numbers.find(searchFor, pos + 1, numbers.size());
    if (pos < numbers.size()) {
        cout << "Found second " << searchFor << " at position " << pos << endl;
    }
    
    cout << "\n6. SORTING:" << endl;
    cout << "============" << endl;
    
    Vector<int> unsorted;
    unsorted.push_back(50);
    unsorted.push_back(10);
    unsorted.push_back(30);
    unsorted.push_back(40);
    unsorted.push_back(20);
    unsorted.display("unsorted");
    
    unsorted.sort();
    unsorted.display("sorted");
    
    cout << "\n7. AUTOMATIC EXPANSION:" << endl;
    cout << "========================" << endl;
    
    Vector<int> small(DEFAULT_CAPACITY);  // Small capacity
    cout << "Initial capacity: " << small.capacity() << endl;
    
    // Add elements until expansion is needed
    for (int i = 1; i <= 10; i++) {
        small.push_back(i * 100);
        cout << "After push_back(" << i * 100 << "): ";
        cout << "size = " << small.size() 
             << ", capacity = " << small.capacity() << endl;
    }
    
    cout << "\n8. DESTRUCTORS AUTOMATICALLY CALLED:" << endl;
    cout << "=====================================" << endl;
    cout << "Vectors will be destroyed when main() ends" << endl;
    cout << "Destructors will free all allocated memory" << endl;
    
    return 0;
}