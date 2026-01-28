#include <bits/stdc++.h>
using Rank = unsigned int; // Rank type for indexing
using namespace std;

// Bitmap: Space-efficient data structure for storing boolean values (bits)
// Instead of using 1 byte per boolean, uses 1 bit per boolean (8x space savings)
// Example: To store 1000 booleans: array needs 1000 bytes, bitmap needs only 125 bytes
class Bitmap {
    private:
    unsigned char * M;  // Pointer to bit array (each byte stores 8 bits)
    Rank N;             // Number of bytes allocated
    Rank _sz;           // Number of bits currently set to 1
    
    public:
    // Constructor: Create bitmap with capacity for n bits
    // (n+7)/8 calculates bytes needed: rounds up to nearest byte
    // Example: n=10 needs 2 bytes (16 bits), n=8 needs 1 byte
    Bitmap(Rank n = 8){
        M = new uint8_t[N = (n+7)/8];  // Allocate byte array
        memset(M, 0, N);                // Initialize all bits to 0
        _sz = 0;                        // No bits set yet
    }
    
    // Destructor: Release allocated memory
    ~Bitmap() {
        delete [] M;
        M = NULL;
        _sz = 0;
    }
    
    // Test if bit k is set (returns true if bit is 1, false if 0)
    // Bit manipulation:
    //   k >> 3 finds which byte (divide by 8)
    //   k & 0x07 finds position within byte (remainder mod 8)
    //   0x80 >> (k&0x07) creates mask with single 1 bit at position
    // Example: k=10 → byte 1 (10/8), position 2 (10%8)
    bool test(Rank k){
        expand(k);  // Ensure bitmap is large enough for bit k
        return M[k >> 3] & (0x80 >> (k&0x07));  // Check if bit is 1
    }
    
    // Set bit k to 1 (mark as true)
    // Uses OR operation (|=) to set bit without affecting others
    void set(Rank k){
        if(test(k)) return;  // Already set, nothing to do
        M[k >> 3] |= (0x80 >> (k&0x07));  // Set the bit to 1
        _sz++;  // Increment count of set bits
    }

    // Clear bit k (set to 0) - should be named clear(), not test()
    // Uses AND with negated mask (~) to clear bit without affecting others
    void clear(Rank k){
        if(!test(k)) return;  // Already 0, nothing to do
        M[k >> 3] &= ~(0x80 >> (k&0x07));  // Clear the bit to 0
        _sz--;  // Decrement count of set bits
    }

};

// Sieve of Eratosthenes: Algorithm to find all prime numbers up to n
// Uses bitmap for space efficiency (1 bit per number instead of 1 byte)
// Algorithm: Mark all multiples of each prime as composite (not prime)
// Time: O(n log log n), Space: O(n/8) bytes
void Eratosthenes(int n, char * file){
    Bitmap B(n);  // Create bitmap with n bits
    B.set(0);     // 0 is not prime, mark as composite
    B.set(1);     // 1 is not prime, mark as composite
    
    // For each number i from 2 to n
    for(int i = 2; i < n; i++){
        if(!B.test(i))  // If i is not marked (i is prime)
            // Mark all multiples of i as composite
            for(int j = 2*i; j < n; j += i)
                B.set(j);  // j is composite (divisible by i)
    }
    // After loop: bits that are 0 represent prime numbers
    B.dump(file);  // Save results to file
}

int main(){

    return 0;
}