#ifndef BASE_CONVERSION_HPP
#define BASE_CONVERSION_HPP

#include "Stack.hpp"
#include <cstdint>
#include <cctype>

// Recursive Version | Head Recursion
// Convert number to specified base using recursion
void convert( uint64_t n, int base ) {
   static char digit[] = "0123456789ABCDEF"; // Digit symbols for bases up to 16
   if ( n < 1 ) return; // Base case: stop recursion
   convert( n / base, base ); // Head recursion: output higher-order digits first
   // output( digit[n % base] ); // Then output lowest digit (can customize output method)
   std::cout << digit[n % base];
} // Time and space complexity: O(log n), but larger constants than iterative version

// Iterative Version | Manual Stack
// Convert number to specified base using explicit stack
void convert_iter( uint64_t n, int base ) {
   static char digit[] = "0123456789ABCDEF";
   Stack<char> S; // Use stack instead of call stack
   while ( 0 < n ) {
      S.push( digit[ n % base ] ); // Get remainder and push digit
      n /= base; // Update quotient
   } // Remainder into stack, quotient for next iteration
   while ( !S.empty() ) 
      std::cout << S.pop(); // Output digits in correct order
} // Time and space complexity: O(log n), but smaller constants than recursive version

#endif // BASE_CONVERSION_HPP