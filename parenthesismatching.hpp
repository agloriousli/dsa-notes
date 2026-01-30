#ifndef PARENTHESIS_MATCHING_HPP
#define PARENTHESIS_MATCHING_HPP

#include "Stack.hpp"
#include <iostream>

// Single type parenthesis matching algorithm
// Determines if parentheses are properly matched (one type only)
bool paren_single( const char A[], Rank n ) {
   Stack<char> S; // Track unmatched left parentheses
   for ( Rank i = 0; i < n; i++ ) { // Sequential scan through string
      if ( '(' == A[i] ) 
         S.push( A[i] ); // Left paren: push to stack
      else if ( ! S.empty() ) 
         S.pop(); // Right paren: pop matching left paren from stack
      else 
         return false; // Right paren without matching left paren
   }
   return S.empty(); // Balanced only if stack is empty at end
}

// Single type parenthesis matching - simplified with counter
// Uses a counter instead of stack to track balance (more efficient for single type)
bool paren_single_counter( const char A[], Rank n ) {
   int s = 0; // Counter equivalent to S.size()
   for ( Rank i = 0; i < n; i++ ) {
      if ( '(' == A[i] ) 
         s++; // Left paren: increment counter
      else {
         s--; // Right paren: decrement counter
         if ( s < 0 ) return false; // Mismatch: more rights than lefts
      }
   }
   return s == 0; // Balanced only if counter returns to zero
}

// Multiple type parenthesis matching algorithm
// Handles (), [], {} - all must be properly matched and nested
bool paren_multiple( const char A[], Rank n ) {
   Stack<char> S; // One stack handles all parenthesis types
   for ( Rank i = 0; i < n; i++ ) { // Sequential scan through string
      switch ( A[i] ) { // Process each character
         case '(': 
         case '[': 
         case '{': 
            S.push( A[i] ); // All left parens: push regardless of type
            break;
         case ')': 
            if ( S.empty() || '(' != S.pop() ) 
               return false; // Right paren must match type of top
            break;
         case ']': 
            if ( S.empty() || '[' != S.pop() ) 
               return false; // Same for square brackets
            break;
         case '}': 
            if ( S.empty() || '{' != S.pop() ) 
               return false; // Same for curly braces
            break;
      }
   }
   return S.empty(); // Balanced only if all parens matched and stack empty
}

#endif // PARENTHESIS_MATCHING_HPP