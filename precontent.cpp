#include <iostream>
#include <string>
using namespace std;

int main() {
    // ==================== DATA TYPES ====================
    
    // Integer types (whole numbers)
    int age = 25;          // Most common (4 bytes, -2B to +2B)
    short small = 100;     // Smaller (2 bytes)
    long big = 1000000;    // Larger (4-8 bytes)

    // Decimal types (floating point)
    float pi = 3.14f;      // Single precision (add 'f')
    double precise = 3.1415926535;  // Double precision (default)

    // Character type
    char grade = 'A';      // Single character (use single quotes)
    char symbol = '$';

    // Boolean type
    bool isRaining = true;  // true or false (1 byte)
    bool hasMoney = false;

    // String (needs #include <string>)
    string name = "Alice";  // Text (use double quotes)

    // ==================== INPUT ====================
    
    int number;
    cout << "Enter a number: ";
    cin >> number;                    // Read integer

    double price;
    cout << "Enter price: ";
    cin >> price;                     // Read decimal

    char initial;
    cout << "Enter initial: ";
    cin >> initial;                   // Read character

    string fullName;
    cout << "Enter name: ";
    cin.ignore();                     // Clear buffer
    getline(cin, fullName);           // Read entire line

    // ==================== OUTPUT ====================
    
    cout << "Hello World!" << endl;   // Print text
    cout << "Number: " << 42 << endl; // Print multiple items
    cout << "Line1\nLine2\nLine3" << endl;  // Multiple lines

    // ==================== OPERATORS ====================
    
    // Arithmetic
    int a = 10, b = 3;
    int sum = a + b;      // 13
    int diff = a - b;     // 7
    int prod = a * b;     // 30
    int quot = a / b;     // 3 (integer division!)
    int mod = a % b;      // 1 (remainder)

    // Assignment
    int x = 5;           // Basic assignment
    x += 3;              // x = x + 3
    x -= 2;              // x = x - 2
    x *= 4;              // x = x * 4
    x /= 2;              // x = x / 2
    x %= 3;              // x = x % 3

    // Increment/Decrement
    int count = 5;
    count++;            // count = 6 (post-increment)
    ++count;            // count = 7 (pre-increment)
    count--;            // count = 6 (post-decrement)
    --count;            // count = 5 (pre-decrement)

    // ==================== COMMON MISTAKES ====================
    
    // CORRECT: With semicolon
    int y = 5; // CORRECT

    // CORRECT: Char uses single quotes
    char c = 'A';  // CORRECT

    // CORRECT: String initialized
    int score = 0;  // ALWAYS initialize!

    // ==================== IF STATEMENTS ====================
    
    // Basic if
    if (age >= 18) {
        cout << "You are an adult" << endl;
    }

    // if-else
    if (score >= 60) {
        cout << "Pass" << endl;
    } else {
        cout << "Fail" << endl;
    }

    // if-else if-else
    if (grade == 'A') {
        cout << "Excellent" << endl;
    } else if (grade == 'B') {
        cout << "Good" << endl;
    } else if (grade == 'C') {
        cout << "Average" << endl;
    } else {
        cout << "Needs improvement" << endl;
    }

    // Nested if
    bool hasLicense = true;
    if (age >= 18) {
        if (hasLicense) {
            cout << "Can drive" << endl;
        }
    }

    // ==================== COMPARISON OPERATORS ====================
    
    int a2 = 5, b2 = 10;
    
    if (a2 == b2) cout << "Equal" << endl;          // Equal to
    if (a2 != b2) cout << "Not equal" << endl;      // Not equal to
    if (a2 < b2) cout << "Less than" << endl;       // Less than
    if (a2 > b2) cout << "Greater than" << endl;    // Greater than
    if (a2 <= b2) cout << "Less or equal" << endl;  // Less than or equal
    if (a2 >= b2) cout << "Greater or equal" << endl; // Greater than or equal

    // ==================== LOGICAL OPERATORS ====================
    
    // AND: both must be true
    if (a2 > 0 && b2 > 0) {
        cout << "Both positive" << endl;
    }

    // OR: at least one true
    if (a2 > 0 || b2 > 0) {
        cout << "At least one positive" << endl;
    }

    // NOT: reverse boolean
    if (!(a2 < 0)) {
        cout << "a is not negative" << endl;
    }

    // ==================== WHILE LOOP ====================
    
    // Basic while
    int count2 = 1;
    while (count2 <= 5) {
        cout << count2 << " ";
        count2++;
    }
    cout << endl;

    // Break statement
    int num = 1;
    while (true) {
        cout << num << " ";
        num++;
        if (num > 5) {
            break;  // Exit loop
        }
    }
    cout << endl;

    // Continue statement
    int i = 0;
    while (i < 10) {
        i++;
        if (i % 2 == 0) {
            continue;  // Skip even numbers
        }
        cout << i << " ";
    }
    cout << endl;

    // ==================== FOR LOOP ====================
    
    // Basic for loop
    for (int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    // Countdown
    for (int i = 5; i > 0; i--) {
        cout << i << " ";
    }
    cout << endl;

    // Skip values
    for (int i = 0; i < 10; i += 2) {
        cout << i << " ";
    }
    cout << endl;

    // Nested loops
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            cout << "(" << i << "," << j << ") ";
        }
        cout << endl;
    }

    // ==================== DO-WHILE LOOP ====================
    
    // Always runs at least once
    int number2;
    do {
        cout << "Enter positive number: ";
        cin >> number2;
    } while (number2 <= 0);

    // ==================== SWITCH STATEMENT ====================
    
    char grade2 = 'B';
    
    switch (grade2) {
        case 'A':
            cout << "Excellent!" << endl;
            break;
        case 'B':
            cout << "Good" << endl;
            break;
        case 'C':
            cout << "Average" << endl;
            break;
        case 'D':
            cout << "Poor" << endl;
            break;
        case 'F':
            cout << "Fail" << endl;
            break;
        default:
            cout << "Invalid grade" << endl;
    }

    // ==================== TYPE CONVERSION ====================
    
    // Implicit (automatic)
    int intNum = 5;
    double doubleNum = intNum;  // 5.0

    double price2 = 9.99;
    int approx = (int)price2;   // 9

    // Explicit (manual)
    double pi2 = 3.14159;
    int approxPi = static_cast<int>(pi2);  // 3

    // char ↔ int
    char letter = 'A';
    int ascii = letter;        // 65
    char nextLetter = char(letter + 1);  // 'B'

    // string ↔ number
    string numStr = "123";
    int number3 = stoi(numStr);  // string to int
    double value = stod("3.14"); // string to double
    string strNum = to_string(42); // number to string

    return 0;
}