#ifndef STACK_PERMUTATION_HPP
#define STACK_PERMUTATION_HPP

#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>

// Stack Permutation Check Algorithm
// Determines if a given permutation B can be obtained through stack operations
Rank spCheck( Vector<Rank>& B ) { // B is the target permutation [1,n]
   Stack<Rank> S; // Intermediate stack for operations
   Rank A = 1; // Next input element to push (input sequence <1,2,3,...,n])
   for ( Rank n = B.size(), r = 0; r < n; ) {
      if ( S.empty() || S.top() != B[r] ) { // Stack empty or top doesn't match
         if ( n < A || B[r] < A ) { // No more elements or element already passed
            return r; // Impossible configuration - stuck here
         }
         else 
            do S.push( A++ ); // Push operation: keep pushing elements
            while ( S.top() != B[r] ); // Until top matches target
      }
      S.pop(); // Pop operation: remove the top element
      r++; // Move to next target element
   }
   return B.size(); // Success - all elements matched successfully
} // spCheck, O(n)

// Catalan number calculation (for counting valid stack permutations)
// Catalan numbers count the number of valid parenthesis sequences and stack permutations
unsigned long long catalan(int n) {
   if (n <= 1) return 1; // Base cases: C(0) = 1, C(1) = 1
   unsigned long long res = 0;
   // Recursive formula: C(n) = sum of C(i) * C(n-i-1) for i from 0 to n-1
   for (int i = 0; i < n; i++)
      res += catalan(i) * catalan(n - i - 1);
   return res;
}

// Stack permutation simulation - verify if sequence can be produced by stack
// Simulates push/pop operations to check if input produces the desired output
bool isStackPermutation(const Vector<Rank>& input, const Vector<Rank>& output) {
   Stack<Rank> S;
   Rank i = 0; // Index for input sequence
   Rank j = 0; // Index for output sequence
   
   while (i < input.size()) {
      S.push(input[i]); // Push next input element
      i++;
      
      // Pop all elements that match next expected output
      while (!S.empty() && S.top() == output[j]) {
         S.pop();
         j++;
      }
   }
   
   // Success if stack is empty and all output elements matched
   return S.empty() && j == output.size();
}

#endif 