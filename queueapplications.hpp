#ifndef QUEUE_APPLICATIONS_HPP
#define QUEUE_APPLICATIONS_HPP

#include "queue.hpp"
#include <cstdlib>  // for rand()

// Application 1: Prefix Sum Calculation
// 任给序列：计算前缀和序列
// Given a sequence, compute the prefix sum sequence
void qPreSum( Queue<int>& A, Rank n ) { 
   int sum = 0; // Accumulated prefix sum
   while ( n-- ) // Iteratively accumulate each element
      A.enqueue( sum += A.dequeue() ); // Dequeue element, add to sum, enqueue sum
} // qSum, O(n)

// Application 2: Sliding Window Sum
// 进一步地，计算滑动窗口和
// Compute sliding window sums by maintaining a window of size w
void qWinSum( Queue<int>& A, Rank n, Rank w ) { // w<=n
   qPreSum( A, n ); // First compute prefix sums
   Queue<int> W; 
   W.enqueue( 0 ); // Initialize window with 0
   
   for ( Rank i = 1; i < w; i++ ) // Fill the window to size w
      W.enqueue( A.dequeue() );
      
   for ( Rank i = w-1; i < n; i++ ) { // Process each window position
      A.enqueue( A.front() - W.dequeue() ); // Calculate window sum as difference
      W.enqueue( A.dequeue() ); // Slide the window forward
   } // for
} // qWinSum, O(n)

// Application 3: Round Robin Scheduling
// 轮转调度模拟
// Simulate round-robin scheduling where each client gets a time quantum
void roundRobinScheduling( Queue<int>& clients, int quantum ) {
   // Queue Q( clients ); // All clients sharing resource form a queue
   // Assume clients is already a queue
   
   while ( !ServiceClosed() ) { // Before service closes, repeatedly:
      int e = clients.dequeue(); // Dequeue the front client and
      serve( e, quantum ); // Serve them for a time quantum, then
      clients.enqueue( e ); // Enqueue them back to the queue
   }
}

// Application 4: Bank/Service Window Simulation
// Simulate a multi-window service system (e.g., bank tellers)
void simu( int winds, int duration ) { // Number of windows, service duration
   Queue<int>* wind = new Queue<int>[winds]; // Each window maintains a queue of service times
   
   while ( duration-- ) { // For each unit of time before closing
      for ( int i = 0; i < winds; i++ ) { // For each window, the front customer
         if ( !wind[i].empty() && ( 1 > wind[i].front()-- ) ) // receives one unit of service
            wind[i].dequeue(); // When service completes, customer leaves queue
      }
      
      if ( rand() % ( 1 + winds ) ) // New customer arrives with probability winds/(winds + 1)
         wind[ rand() % winds ].enqueue( 1 + rand() % 99 ); // Random window, random service duration
   } // for
   
   delete [] wind; // Free all queues
} // simu

#endif // QUEUE_APPLICATIONS_HPP