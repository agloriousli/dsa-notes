#ifndef REVERSE_ALGORITHMS_HPP
#define REVERSE_ALGORITHMS_HPP

#include <vector>
#include <iostream>

// Rank-based access version
// Reverse using rank-based indexing - swap elements from both ends moving inward
std::vector<int> reverse_1(std::vector<int> L) {
   int lo = 0, hi = L.size() - 1;
   while (lo < hi) {
      std::swap(L[lo], L[hi]); // Swap elements at low and high positions
      lo++;
      hi--; // Move pointers toward center
   }
   return L;
}

// Position-based access version
// Reverse by repeatedly moving the last element to position i (less efficient)
std::vector<int> reverse_2(std::vector<int> L) {
   for (size_t i = 0; i < L.size(); i++) {
      int temp = L.back(); // Get last element
      L.pop_back(); // Remove it from back
      L.insert(L.begin() + i, temp); // Insert at position i
   }
   return L;
}

#endif 