#ifndef RECURSION_HPP
#define RECURSION_HPP

#include <iostream>

// 递归函数示例

int fac(int n) { 
   return (n < 2) ? 1 : n * fac(n - 1); 
}

int fib( int n ) { 
   return (n < 2) ? n : fib(n - 1) + fib(n - 2); 
}

// Hailstone sequence functions
void hailstone(int n) { 
   if ( 1 < n ) n % 2  ?  odd( n ) : even( n ); 
}

void even( int n ) { 
   hailstone( n / 2 ); 
}

void odd( int n ) { 
   hailstone( 3*n + 1 ); 
}

// Reverse array using recursion
void reverse( int * A, int n ) { 
   if ( n < 2 ) return; 
   std::swap( A[0], A[n - 1] ); 
   reverse( A + 1, n - 2 ); 
}

// Tail-recursive version of reverse
void reverse_tail(int* A, int n) {
   if (n < 2) return;
   std::swap(A[0], A[n-1]);
   A++; n -= 2;
   reverse_tail(A, n);
}

// Iterative version of reverse
void reverse_iter(int* A, int n) {
   next: //转向标志
   if (n < 2) return;
   std::swap(A[0], A[n-1]);
   A++; n -= 2;
   goto next; //模拟递归返回
}

// Fully iterative version of reverse
void reverse_iter_full(int* A, int n) {
   while (1 < n) {
      std::swap(A[0], A[n-1]);
      A++; n -= 2;
   }
}

// 消除递归的版本

int fac_iter( int n ) { 
   int f = 1; //O(1)空间
   while ( n > 1 ) f *= n--;
   return f; 
}

void hailstone_iter( int n ) { //O(1)空间
   while ( 1 < n ) n = n % 2 ? 3*n + 1 : n/2; 
}

int fib_iter( int n ) { //O(1)空间
   int f = 0, g = 1;
   while ( 0 < n-- ) {
      g += f;
      f = g - f;
   }
   return f;
}

#endif // RECURSION_HPP