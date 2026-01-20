#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ==================== PHASE 1: C++ BASICS ====================

void phase1_datatypes() {
    cout << "\n=== PHASE 1: DATA TYPES ===" << endl;
    
    // Integer types - whole numbers
    int age = 25;              // 4 bytes, range: -2,147,483,648 to 2,147,483,647
    short smallNum = 100;      // 2 bytes, range: -32,768 to 32,767
    long bigNum = 1000000;     // 4-8 bytes (platform dependent)
    
    // Decimal types - numbers with fractals
    float pi = 3.14f;          // 4 bytes, ~7 decimal digits precision
    double precise = 3.14159;  // 8 bytes, ~15 decimal digits precision
    
    // Character - single letter/symbol
    char letter = 'A';         // 1 byte, must use SINGLE quotes
    
    // Boolean - true/false
    bool isStudent = true;     // 1 byte, only two values: true or false
    
    // String - text
    string name = "Alice";     // Must use DOUBLE quotes
    
    cout << "Age: " << age << endl;
    cout << "Pi: " << pi << endl;
    cout << "Letter: " << letter << endl;
    cout << "Is student? " << isStudent << endl;
}

void phase1_input_output() {
    cout << "\n=== PHASE 1: INPUT & OUTPUT ===" << endl;
    
    // OUTPUT: cout (console output)
    cout << "Hello World!" << endl;     // Print text and newline
    cout << "Number: " << 42 << endl;   // Print multiple things
    
    // INPUT: cin (console input)
    int number;
    cout << "Enter a number: ";
    cin >> number;                      // Read integer from keyboard
    cout << "You entered: " << number << endl;
    
    // Reading strings (single word)
    string word;
    cout << "Enter a word: ";
    cin >> word;                        // Stops at space
    cout << "Word: " << word << endl;
    
    // Reading full line (with spaces)
    string sentence;
    cout << "Enter a sentence: ";
    cin.ignore();                       // Clear input buffer (important!)
    getline(cin, sentence);             // Read entire line
    cout << "Sentence: " << sentence << endl;
}

void phase1_operators() {
    cout << "\n=== PHASE 1: OPERATORS ===" << endl;
    
    // ARITHMETIC OPERATORS
    int a = 10, b = 3;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << (a + b) << endl;  // 13 - addition
    cout << "a - b = " << (a - b) << endl;  // 7  - subtraction
    cout << "a * b = " << (a * b) << endl;  // 30 - multiplication
    cout << "a / b = " << (a / b) << endl;  // 3  - division (integer!)
    cout << "a % b = " << (a % b) << endl;  // 1  - remainder (modulo)
    
    // ASSIGNMENT OPERATORS
    int x = 5;      // Basic assignment
    cout << "\nInitial x = " << x << endl;
    x += 3;         // Same as: x = x + 3
    cout << "After x += 3: " << x << endl;  // 8
    x -= 2;         // Same as: x = x - 2
    cout << "After x -= 2: " << x << endl;  // 6
    x *= 4;         // Same as: x = x * 4
    cout << "After x *= 4: " << x << endl;  // 24
    x /= 2;         // Same as: x = x / 2
    cout << "After x /= 2: " << x << endl;  // 12
    
    // INCREMENT/DECREMENT
    int count = 5;
    cout << "\nInitial count = " << count << endl;
    count++;        // Add 1 (post-increment)
    cout << "After count++: " << count << endl;  // 6
    ++count;        // Add 1 (pre-increment)
    cout << "After ++count: " << count << endl;  // 7
    count--;        // Subtract 1 (post-decrement)
    cout << "After count--: " << count << endl;  // 6
    
    // COMPARISON OPERATORS (return true/false)
    cout << "\nComparison operators:" << endl;
    cout << "10 == 10: " << (10 == 10) << endl;  // 1 (true) - equal
    cout << "10 != 5: " << (10 != 5) << endl;    // 1 (true) - not equal
    cout << "10 > 5: " << (10 > 5) << endl;      // 1 (true) - greater
    cout << "10 < 5: " << (10 < 5) << endl;      // 0 (false) - less
    cout << "10 >= 10: " << (10 >= 10) << endl;  // 1 (true) - greater or equal
    cout << "10 <= 5: " << (10 <= 5) << endl;    // 0 (false) - less or equal
}

void phase1_control_flow() {
    cout << "\n=== PHASE 1: CONTROL FLOW ===" << endl;
    
    // IF STATEMENT - make decisions
    int age = 20;
    cout << "Age: " << age << endl;
    
    if (age >= 18) {                    // Condition in parentheses
        cout << "You are an adult" << endl;  // Code runs if true
    }
    
    // IF-ELSE - two choices
    int score = 75;
    cout << "\nScore: " << score << endl;
    
    if (score >= 60) {
        cout << "Pass" << endl;
    } else {                            // Runs if condition is false
        cout << "Fail" << endl;
    }
    
    // IF-ELSE IF-ELSE - multiple choices
    char grade = 'B';
    cout << "\nGrade: " << grade << endl;
    
    if (grade == 'A') {
        cout << "Excellent!" << endl;
    } else if (grade == 'B') {          // Check next condition
        cout << "Good" << endl;
    } else if (grade == 'C') {
        cout << "Average" << endl;
    } else {                            // None of above
        cout << "Needs improvement" << endl;
    }
    
    // LOGICAL OPERATORS
    bool hasLicense = true;
    int driverAge = 20;
    
    // AND (&&) - both must be true
    if (driverAge >= 18 && hasLicense) {
        cout << "\nCan drive legally" << endl;
    }
    
    // OR (||) - at least one must be true
    if (driverAge < 16 || !hasLicense) {
        cout << "Cannot drive" << endl;
    } else {
        cout << "Can drive" << endl;
    }
}

void phase1_loops() {
    cout << "\n=== PHASE 1: LOOPS ===" << endl;
    
    // FOR LOOP - when you know how many times
    cout << "For loop (0 to 4): ";
    for (int i = 0; i < 5; i++) {       // initialize; condition; increment
        cout << i << " ";
    }
    cout << endl;
    
    // Breakdown of for loop:
    // int i = 0;     <- runs once at start
    // i < 5;         <- checked before each iteration
    // i++            <- runs after each iteration
    
    // FOR LOOP - countdown
    cout << "Countdown: ";
    for (int i = 5; i > 0; i--) {
        cout << i << " ";
    }
    cout << endl;
    
    // WHILE LOOP - when you don't know how many times
    cout << "While loop: ";
    int count = 1;
    while (count <= 5) {                // Keep going while true
        cout << count << " ";
        count++;                        // Don't forget to increment!
    }
    cout << endl;
    
    // DO-WHILE LOOP - always runs at least once
    int num;
    cout << "Enter positive number: ";
    do {
        cin >> num;
        if (num <= 0) {
            cout << "Try again (positive): ";
        }
    } while (num <= 0);                 // Condition checked at end
    cout << "You entered: " << num << endl;
    
    // BREAK - exit loop early
    cout << "Break example: ";
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            break;                      // Stop loop immediately
        }
        cout << i << " ";
    }
    cout << endl;
    
    // CONTINUE - skip to next iteration
    cout << "Continue example (skip evens): ";
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;                   // Skip rest of this iteration
        }
        cout << i << " ";
    }
    cout << endl;
}

void phase1_arrays() {
    cout << "\n=== PHASE 1: ARRAYS ===" << endl;
    
    // ARRAY DECLARATION - fixed size, same type
    int numbers[5];                     // Creates 5 integers (uninitialized)
    
    // ARRAY INITIALIZATION
    int scores[5] = {90, 85, 88, 92, 87};  // Initialize with values
    
    // ACCESSING ELEMENTS - use index (starts at 0!)
    cout << "First score: " << scores[0] << endl;   // 90
    cout << "Third score: " << scores[2] << endl;   // 88
    cout << "Last score: " << scores[4] << endl;    // 87
    
    // MODIFYING ELEMENTS
    scores[1] = 95;                     // Change second element
    cout << "Updated second score: " << scores[1] << endl;
    
    // LOOPING THROUGH ARRAY
    cout << "All scores: ";
    for (int i = 0; i < 5; i++) {       // i goes from 0 to 4
        cout << scores[i] << " ";
    }
    cout << endl;
    
    // ARRAY SIZE - must track yourself!
    int size = 5;                       // Arrays don't know their size
    
    // COMMON ARRAY OPERATIONS
    // 1. Sum all elements
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    cout << "Sum: " << sum << endl;
    
    // 2. Find maximum
    int max = scores[0];                // Assume first is max
    for (int i = 1; i < size; i++) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }
    cout << "Maximum: " << max << endl;
    
    // 3. Find element
    int target = 88;
    int position = -1;                  // -1 means not found
    for (int i = 0; i < size; i++) {
        if (scores[i] == target) {
            position = i;
            break;
        }
    }
    if (position != -1) {
        cout << target << " found at index " << position << endl;
    }
}

// ==================== PHASE 2: POINTERS & MEMORY ====================

void phase2_pointers_basics() {
    cout << "\n=== PHASE 2: POINTERS BASICS ===" << endl;
    
    // REGULAR VARIABLE
    int age = 25;
    cout << "age = " << age << endl;                    // Value: 25
    cout << "Address of age: " << &age << endl;         // Memory address
    
    // POINTER - stores memory address
    int* ptr;                           // Declare pointer to int
    ptr = &age;                         // ptr now points to age
    
    cout << "\nPointer ptr:" << endl;
    cout << "Value of ptr (address): " << ptr << endl;  // Address it points to
    cout << "Value at address (*ptr): " << *ptr << endl; // Dereference: get value
    
    // CHANGING VALUE THROUGH POINTER
    *ptr = 30;                          // Change value at address
    cout << "\nAfter *ptr = 30:" << endl;
    cout << "age = " << age << endl;    // age changed to 30!
    
    // WHY USE POINTERS?
    // 1. Pass large data without copying
    // 2. Modify variables in functions
    // 3. Dynamic memory allocation
}

void phase2_dynamic_memory() {
    cout << "\n=== PHASE 2: DYNAMIC MEMORY ===" << endl;
    
    // STACK vs HEAP
    // Stack: automatic, fixed size, limited
    int stackArray[5];                  // Size must be constant
    
    // Heap: manual, any size, unlimited (but slower)
    int* heapArray = new int[5];        // Allocate 5 integers on heap
    
    // USE DYNAMIC ARRAY
    heapArray[0] = 10;
    heapArray[1] = 20;
    heapArray[2] = 30;
    cout << "heapArray[0] = " << heapArray[0] << endl;
    cout << "heapArray[1] = " << heapArray[1] << endl;
    
    // MUST FREE MEMORY (or memory leak!)
    delete[] heapArray;                 // Free array
    heapArray = nullptr;                // Good practice: set to null
    
    // DYNAMIC SIZE - read size at runtime
    int size;
    cout << "Enter array size: ";
    cin >> size;
    
    int* dynamicArray = new int[size];  // Size determined at runtime!
    
    // Fill with values
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i * 10;
    }
    
    // Print values
    cout << "Dynamic array: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // ALWAYS DELETE!
    delete[] dynamicArray;
    
    // MEMORY LEAK EXAMPLE (BAD!)
    // int* leak = new int[100];
    // // ... forgot to delete[]
    // leak = new int[200];              // Lost reference to first 100!
    // // Now can never free first allocation
}

void phase2_pass_by_value_reference() {
    cout << "\n=== PHASE 2: PASS BY VALUE vs REFERENCE ===" << endl;
    
    // Helper functions defined below
    auto passByValue = [](int x) {
        x = 100;                        // Changes LOCAL copy only
        cout << "Inside function: x = " << x << endl;
    };
    
    auto passByReference = [](int& x) {
        x = 100;                        // Changes ORIGINAL variable!
        cout << "Inside function: x = " << x << endl;
    };
    
    // PASS BY VALUE
    cout << "Pass by value:" << endl;
    int num1 = 50;
    cout << "Before: num1 = " << num1 << endl;
    passByValue(num1);                  // Makes copy
    cout << "After: num1 = " << num1 << endl;  // Still 50!
    
    // PASS BY REFERENCE
    cout << "\nPass by reference:" << endl;
    int num2 = 50;
    cout << "Before: num2 = " << num2 << endl;
    passByReference(num2);              // Uses original
    cout << "After: num2 = " << num2 << endl;  // Changed to 100!
}

// ==================== PHASE 3: CLASSES & OOP ====================

// SIMPLE CLASS EXAMPLE
class Box {
private:                                // Only accessible inside class
    int width;
    int height;
    
public:                                 // Accessible from outside
    // CONSTRUCTOR - runs when object is created
    Box(int w, int h) {
        width = w;
        height = h;
        cout << "Box created: " << width << "x" << height << endl;
    }
    
    // DESTRUCTOR - runs when object is destroyed
    ~Box() {
        cout << "Box destroyed" << endl;
    }
    
    // GETTER - access private data
    int getWidth() {
        return width;
    }
    
    int getHeight() {
        return height;
    }
    
    // SETTER - modify private data
    void setWidth(int w) {
        if (w > 0) {                    // Can add validation!
            width = w;
        }
    }
    
    // MEMBER FUNCTION - uses class data
    int area() {
        return width * height;
    }
    
    // MEMBER FUNCTION - can modify data
    void resize(int w, int h) {
        width = w;
        height = h;
    }
};

void phase3_classes_basics() {
    cout << "\n=== PHASE 3: CLASSES BASICS ===" << endl;
    
    // CREATE OBJECT (calls constructor)
    Box myBox(10, 5);
    
    // USE MEMBER FUNCTIONS
    cout << "Width: " << myBox.getWidth() << endl;
    cout << "Height: " << myBox.getHeight() << endl;
    cout << "Area: " << myBox.area() << endl;
    
    // MODIFY OBJECT
    myBox.setWidth(20);
    cout << "New area: " << myBox.area() << endl;
    
    myBox.resize(15, 8);
    cout << "After resize: " << myBox.area() << endl;
    
    // Object destroyed here (destructor called)
}

// SIMPLE ARRAY CLASS - mimics built-in array
class SimpleArray {
private:
    int* data;                          // Pointer to dynamic array
    int capacity;                       // Max size
    int size;                           // Current elements
    
public:
    // CONSTRUCTOR
    SimpleArray(int cap) {
        capacity = cap;
        size = 0;
        data = new int[capacity];       // Allocate memory
        cout << "SimpleArray created (capacity " << capacity << ")" << endl;
    }
    
    // DESTRUCTOR
    ~SimpleArray() {
        delete[] data;                  // Free memory!
        cout << "SimpleArray destroyed" << endl;
    }
    
    // ADD ELEMENT
    void add(int value) {
        if (size < capacity) {
            data[size] = value;
            size++;
        } else {
            cout << "Array full!" << endl;
        }
    }
    
    // GET ELEMENT
    int get(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;                      // Error value
    }
    
    // GET SIZE
    int getSize() {
        return size;
    }
    
    // PRINT ALL
    void print() {
        cout << "Array: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
    
    // OPERATOR OVERLOAD - access like array
    int& operator[](int index) {
        return data[index];             // Returns reference (can modify)
    }
};

void phase3_custom_array() {
    cout << "\n=== PHASE 3: CUSTOM ARRAY CLASS ===" << endl;
    
    // CREATE ARRAY OBJECT
    SimpleArray arr(5);
    
    // ADD ELEMENTS
    arr.add(10);
    arr.add(20);
    arr.add(30);
    arr.print();
    
    // ACCESS ELEMENTS
    cout << "Element at index 1: " << arr.get(1) << endl;
    
    // USE OVERLOADED OPERATOR
    cout << "Using []: arr[1] = " << arr[1] << endl;
    arr[1] = 99;                        // Modify through operator
    arr.print();
}

// ==================== PHASE 4: TEMPLATES ====================

// TEMPLATE FUNCTION - works with any type
template <typename T>
T getMax(T a, T b) {
    return (a > b) ? a : b;             // Ternary operator
}

void phase4_template_function() {
    cout << "\n=== PHASE 4: TEMPLATE FUNCTION ===" << endl;
    
    // WORKS WITH INT
    int maxInt = getMax(10, 20);
    cout << "Max int: " << maxInt << endl;
    
    // WORKS WITH DOUBLE
    double maxDouble = getMax(3.14, 2.71);
    cout << "Max double: " << maxDouble << endl;
    
    // WORKS WITH CHAR
    char maxChar = getMax('A', 'Z');
    cout << "Max char: " << maxChar << endl;
    
    // Same function, different types!
}

// TEMPLATE CLASS - generic container
template <typename T>
class GenericArray {
private:
    T* data;                            // Works with any type T
    int capacity;
    int size;
    
public:
    GenericArray(int cap) {
        capacity = cap;
        size = 0;
        data = new T[capacity];
    }
    
    ~GenericArray() {
        delete[] data;
    }
    
    void add(T value) {                 // T can be int, double, string, etc.
        if (size < capacity) {
            data[size] = value;
            size++;
        }
    }
    
    T get(int index) {
        return data[index];
    }
    
    int getSize() {
        return size;
    }
    
    void print() {
        cout << "Array: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

void phase4_template_class() {
    cout << "\n=== PHASE 4: TEMPLATE CLASS ===" << endl;
    
    // ARRAY OF INTEGERS
    GenericArray<int> intArr(5);
    intArr.add(10);
    intArr.add(20);
    intArr.add(30);
    intArr.print();
    
    // ARRAY OF DOUBLES
    GenericArray<double> doubleArr(3);
    doubleArr.add(3.14);
    doubleArr.add(2.71);
    doubleArr.add(1.41);
    doubleArr.print();
    
    // ARRAY OF STRINGS
    GenericArray<string> stringArr(3);
    stringArr.add("Hello");
    stringArr.add("World");
    stringArr.add("!");
    stringArr.print();
}

// ==================== PHASE 5: STL VECTOR ====================

void phase5_stl_vector_basics() {
    cout << "\n=== PHASE 5: STL VECTOR BASICS ===" << endl;
    
    // CREATE VECTOR
    vector<int> v;                      // Empty vector
    cout << "Initial size: " << v.size() << endl;
    
    // ADD ELEMENTS
    v.push_back(10);                    // Add to end
    v.push_back(20);
    v.push_back(30);
    cout << "After push_back, size: " << v.size() << endl;
    
    // ACCESS ELEMENTS
    cout << "v[0] = " << v[0] << endl;
    cout << "v[1] = " << v[1] << endl;
    cout << "v.at(2) = " << v.at(2) << endl;  // Safer (checks bounds)
    
    // MODIFY ELEMENTS
    v[1] = 99;
    cout << "After v[1] = 99: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    // REMOVE LAST ELEMENT
    v.pop_back();
    cout << "After pop_back: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

void phase5_stl_vector_initialization() {
    cout << "\n=== PHASE 5: VECTOR INITIALIZATION ===" << endl;
    
    // METHOD 1: Empty vector
    vector<int> v1;
    cout << "v1 size: " << v1.size() << endl;
    
    // METHOD 2: With initial values
    vector<int> v2 = {10, 20, 30, 40, 50};
    cout << "v2: ";
    for (int x : v2) cout << x << " ";
    cout << endl;
    
    // METHOD 3: Fixed size with default value
    vector<int> v3(5, 100);             // 5 elements, all 100
    cout << "v3: ";
    for (int x : v3) cout << x << " ";
    cout << endl;
    
    // METHOD 4: Fixed size (default initialized)
    vector<int> v4(3);                  // 3 elements, all 0
    cout << "v4: ";
    for (int x : v4) cout << x << " ";
    cout << endl;
}

void phase5_stl_vector_operations() {
    cout << "\n=== PHASE 5: VECTOR OPERATIONS ===" << endl;
    
    vector<int> v = {10, 20, 30, 40, 50};
    
    // SIZE & CAPACITY
    cout << "Size: " << v.size() << endl;
    cout << "Capacity: " << v.capacity() << endl;
    cout << "Empty? " << v.empty() << endl;
    
    // FRONT & BACK
    cout << "Front: " << v.front() << endl;     // First element
    cout << "Back: " << v.back() << endl;       // Last element
    
    // CLEAR
    v.clear();
    cout << "After clear, size: " << v.size() << endl;
    
    // REFILL
    v = {10, 20, 30, 40, 50};
    
    // INSERT at position
    v.insert(v.begin() + 2, 99);        // Insert 99 at index 2
    cout << "After insert: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // ERASE single element
    v.erase(v.begin() + 1);             // Remove element at index 1
    cout << "After erase: ";
    for (int x : v) cout << x << " ";
    cout << endl;
    
    // ERASE range
    v.erase(v.begin() + 1, v.begin() + 3);  // Remove indices 1-2
    cout << "After range erase: ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

void phase5_stl_vector_iterators() {
    cout << "\n=== PHASE 5: VECTOR ITERATORS ===" << endl;
    
    vector<int> v = {10, 20, 30, 40, 50};
    
    // ITERATOR - pointer-like object
    vector<int>::iterator it;
    
    // LOOP WITH ITERATOR
    cout << "Using iterator: ";
    for (it = v.begin(); it != v.end(); it++) {
        cout << *it << " ";             // Dereference to get value
    }
    cout << endl;
    
    // RANGE-BASED FOR (easier!)
    cout << "Using range-for: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;
    
    // MODIFY THROUGH ITERATOR
    for (int& x : v) {                  // Reference allows modification
        x *= 2;
    }
    cout << "After doubling: ";
    for (int x : v) cout << x << " ";
    cout << endl;
}

// ==================== PHASE 6: UNDERSTANDING TARGET CODE ====================

void phase6_target_code_explained() {
    cout << "\n=== PHASE 6: TARGET CODE BREAKDOWN ===" << endl;
    
    // LINE 1: vector<int> v;
    vector<int> v;                      // Empty vector of integers
    cout << "Created empty vector v" << endl;
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // LINE 2: vector<int> s(81, 25);
    vector<int> s(81, 25);              // 81 elements, all value 25
    cout << "\nCreated vector s with 81 elements (all 25)" << endl;
    cout << "First few: " << s[0] << " " << s[1] << " " << s[2] << endl;
    cout << "Size: " << s.size() << endl;
    
    // LINE 3: s.insert(s.begin() + 5, 2025);
    s.insert(s.begin() + 5, 2025);      // Insert 2025 at position 5
    cout << "\nInserted 2025 at index 5" << endl;
    cout << "Elements 4-7: " << s[4] << " " << s[5] << " " << s[6] << " " << s[7] << endl;
    cout << "Size now: " << s.size() << endl;  // 82 elements now
    
    // LINE 4: s.erase(s.end() - 75, s.end());
    s.erase(s.end() - 75, s.end());     // Remove last 75 elements
    cout << "\nErased last 75 elements" << endl;
    cout << "Size now: " << s.size() << endl;  // 7 elements left
    
    // LINE 5-6: for loop to print
    cout << "Final contents:" << endl;
    for (int i = 0; i < s.size(); i++) {
        cout << s[i] << endl;
    }
    
    // WHAT THIS CODE DOES:
    // 1. Creates vector with 81 elements (all 25)
    // 2. Inserts 2025 at position 5 (now 82 elements)
    // 3. Removes last 75 elements (leaves 7)
    // 4. Prints remaining: 25 25 25 25 25 2025 25
}

void phase6_vector_class_structure() {
    cout << "\n=== PHASE 6: VECTOR CLASS STRUCTURE ===" << endl;
    
    cout << "How vector<T> works internally:" << endl;
    cout << "--------------------------------" << endl;
    cout << "template <typename T>" << endl;
    cout << "class Vector {" << endl;
    cout << "private:" << endl;
    cout << "    T* _elem;        // Pointer to dynamic array" << endl;
    cout << "    int _capacity;   // Max size before reallocation" << endl;
    cout << "    int _size;       // Current number of elements" << endl;
    cout << "" << endl;
    cout << "public:" << endl;
    cout << "    Vector() {" << endl;
    cout << "        _capacity = 2;            // Start small" << endl;
    cout << "        _size = 0;" << endl;
    cout << "        _elem = new T[_capacity]; // Allocate array" << endl;
    cout << "    }" << endl;
    cout << "" << endl;
    cout << "    void push_back(T value) {" << endl;
    cout << "        if (_size == _capacity) {" << endl;
    cout << "            expand();             // Double capacity" << endl;
    cout << "        }" << endl;
    cout << "        _elem[_size] = value;" << endl;
    cout << "        _size++;" << endl;
    cout << "    }" << endl;
    cout << "" << endl;
    cout << "    T& operator[](int index) {" << endl;
    cout << "        return _elem[index];      // Array access" << endl;
    cout << "    }" << endl;
    cout << "};" << endl;
}

// ==================== MAIN FUNCTION ====================

int main() {
    cout << "========================================" << endl;
    cout << "  C++ BASICS TO VECTOR - COMPLETE GUIDE" << endl;
    cout << "========================================" << endl;
    
    // Uncomment sections as you learn:
    
    // PHASE 1: C++ BASICS
    phase1_datatypes();
    phase1_input_output();
    phase1_operators();
    phase1_control_flow();
    phase1_loops();
    phase1_arrays();
    
    // PHASE 2: POINTERS & MEMORY
    phase2_pointers_basics();
    phase2_dynamic_memory();
    phase2_pass_by_value_reference();
    
    // PHASE 3: CLASSES & OOP
    phase3_classes_basics();
    phase3_custom_array();
    
    // PHASE 4: TEMPLATES
    phase4_template_function();
    phase4_template_class();
    
    // PHASE 5: STL VECTOR
    phase5_stl_vector_basics();
    phase5_stl_vector_initialization();
    phase5_stl_vector_operations();
    phase5_stl_vector_iterators();
    
    // PHASE 6: TARGET CODE
    phase6_target_code_explained();
    phase6_vector_class_structure();
    
    cout << "\n========================================" << endl;
    cout << "  END OF GUIDE" << endl;
    cout << "========================================" << endl;
    
    return 0;
}