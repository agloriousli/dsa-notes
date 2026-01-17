#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_set>
#include <ctime>
using namespace std;

// ==================== 1. SIZE & EMPTY ====================
void demoSizeEmpty() {
    cout << "=== size()/empty() Demo ===" << endl;
    
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2;
    
    cout << "v1 size: " << v1.size() << endl;
    cout << "v2 size: " << v2.size() << endl;
    cout << "v1 empty? " << (v1.empty() ? "Yes" : "No") << endl;
    cout << "v2 empty? " << (v2.empty() ? "Yes" : "No") << endl;
    
    // Clear and check
    v1.clear();
    cout << "After clear - v1 size: " << v1.size() 
         << ", empty? " << (v1.empty() ? "Yes" : "No") << endl;
    cout << endl;
}

// ==================== 2. INSERT ====================
void demoInsert() {
    cout << "=== insert(r,e) Demo ===" << endl;
    
    vector<int> v = {10, 20, 30, 40};
    cout << "Original: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Insert at position 2 (0-based)
    v.insert(v.begin() + 2, 99);
    cout << "After insert at rank 2: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Insert multiple copies
    v.insert(v.begin() + 1, 3, 88);  // Insert three 88s
    cout << "After inserting 3 copies of 88: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Insert from another vector
    vector<int> newElems = {100, 200, 300};
    v.insert(v.end() - 1, newElems.begin(), newElems.end());
    cout << "After inserting range: ";
    for (int n : v) cout << n << " ";
    cout << endl << endl;
}

// ==================== 3. REMOVE ====================
void demoRemove() {
    cout << "=== remove(r) Demo ===" << endl;
    
    vector<int> v = {10, 20, 30, 40, 50, 60, 70};
    cout << "Original: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Remove element at rank 2
    v.erase(v.begin() + 2);
    cout << "After remove rank 2: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Remove range (ranks 1-3)
    v.erase(v.begin() + 1, v.begin() + 4);
    cout << "After remove ranks 1-3: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Remove all elements with value 20
    v = {10, 20, 30, 20, 40, 20, 50};
    v.erase(remove(v.begin(), v.end(), 20), v.end());
    cout << "After removing all 20s: ";
    for (int n : v) cout << n << " ";
    cout << endl << endl;
}

// ==================== 4. SORT & UNSORT ====================
void demoSortUnsort() {
    cout << "=== sort()/unsort() Demo ===" << endl;
    
    vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    cout << "Original: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Sort ascending
    sort(v.begin(), v.end());
    cout << "After sort (ascending): ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Sort descending
    sort(v.begin(), v.end(), greater<int>());
    cout << "After sort (descending): ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Custom sort
    v = {15, 23, 8, 42, 4, 16};
    sort(v.begin(), v.end(), [](int a, int b) {
        return a % 10 < b % 10;  // Sort by last digit
    });
    cout << "Sorted by last digit: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Unsort (shuffle)
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);
    cout << "After shuffle: ";
    for (int n : v) cout << n << " ";
    cout << endl << endl;
}

// ==================== 5. FIND & SEARCH ====================
void demoFindSearch() {
    cout << "=== find(e)/search(e) Demo ===" << endl;
    
    vector<int> v = {30, 10, 50, 20, 40, 20, 60};
    cout << "Vector: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // find() - linear search in unsorted
    auto it = find(v.begin(), v.end(), 20);
    if (it != v.end()) {
        int index = distance(v.begin(), it);
        cout << "find(20): Found at rank " << index << endl;
    }
    
    // Find all occurrences
    cout << "All positions of 20: ";
    it = v.begin();
    while ((it = find(it, v.end(), 20)) != v.end()) {
        cout << distance(v.begin(), it) << " ";
        ++it;
    }
    cout << endl;
    
    // binary_search() - requires sorted
    sort(v.begin(), v.end());
    cout << "Sorted vector: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    bool exists = binary_search(v.begin(), v.end(), 40);
    cout << "binary_search(40): " << (exists ? "Found" : "Not found") << endl;
    
    // lower_bound and upper_bound
    auto lb = lower_bound(v.begin(), v.end(), 20);
    auto ub = upper_bound(v.begin(), v.end(), 20);
    cout << "Range of value 20: from rank " << distance(v.begin(), lb)
         << " to " << distance(v.begin(), ub) - 1 << endl;
    
    // equal_range
    auto eq = equal_range(v.begin(), v.end(), 20);
    cout << "equal_range for 20: ";
    for (auto it = eq.first; it != eq.second; ++it) {
        cout << *it << " ";
    }
    cout << endl << endl;
}

// ==================== 6. DEDUP & UNIQUIFY ====================
void demoDedupUniquify() {
    cout << "=== dedup()/uniquify() Demo ===" << endl;
    
    // dedup - for unsorted vectors
    vector<int> unsorted = {3, 1, 2, 2, 1, 3, 4, 5, 4, 2, 1};
    cout << "Unsorted original: ";
    for (int n : unsorted) cout << n << " ";
    cout << endl;
    
    // Method 1: Sort + unique
    vector<int> v1 = unsorted;
    sort(v1.begin(), v1.end());
    auto last = unique(v1.begin(), v1.end());
    v1.erase(last, v1.end());
    cout << "After dedup (sorted method): ";
    for (int n : v1) cout << n << " ";
    cout << endl;
    
    // Method 2: Using unordered_set
    vector<int> v2 = unsorted;
    unordered_set<int> seen;
    vector<int> result;
    for (int n : v2) {
        if (seen.insert(n).second) {  // Insert returns pair
            result.push_back(n);
        }
    }
    cout << "After dedup (hash set method): ";
    for (int n : result) cout << n << " ";
    cout << endl;
    
    // uniquify - for sorted vectors
    vector<int> sorted = {1, 1, 2, 2, 2, 3, 3, 4, 5, 5, 5};
    cout << "Sorted original: ";
    for (int n : sorted) cout << n << " ";
    cout << endl;
    
    auto new_end = unique(sorted.begin(), sorted.end());
    sorted.erase(new_end, sorted.end());
    cout << "After uniquify: ";
    for (int n : sorted) cout << n << " ";
    cout << endl << endl;
}

// ==================== 7. TRAVERSE ====================
void demoTraverse() {
    cout << "=== traverse(visit()) Demo ===" << endl;
    
    vector<int> v = {1, 2, 3, 4, 5};
    cout << "Original: ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Method 1: Range-based for loop (C++11)
    cout << "Range-based for: ";
    for (int n : v) {
        cout << n * 2 << " ";  // Double each element
    }
    cout << endl;
    
    // Method 2: Traditional iterator
    cout << "Iterator traversal: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        *it += 10;  // Modify in place
        cout << *it << " ";
    }
    cout << endl;
    
    // Method 3: for_each with lambda
    cout << "for_each with lambda: ";
    for_each(v.begin(), v.end(), [](int& n) {
        n -= 5;  // Subtract 5 from each
        cout << n << " ";
    });
    cout << endl;
    
    // Method 4: Function object
    struct Multiplier {
        int factor;
        void operator()(int& n) {
            n *= factor;
        }
    };
    
    Multiplier mult{3};
    for_each(v.begin(), v.end(), mult);
    cout << "After multiplier(3): ";
    for (int n : v) cout << n << " ";
    cout << endl;
    
    // Method 5: Index-based traversal
    cout << "Index-based: ";
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = i * 10;  // Assign new values
        cout << v[i] << " ";
    }
    cout << endl << endl;
}

// ==================== 8. COMPREHENSIVE EXAMPLE ====================
void comprehensiveExample() {
    cout << "=== COMPREHENSIVE EXAMPLE ===" << endl;
    
    // Create vector with random data
    vector<int> data;
    for (int i = 0; i < 10; ++i) {
        data.push_back(rand() % 50 + 1);  // Random 1-50
    }
    
    cout << "Original random data: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // Sort
    sort(data.begin(), data.end());
    cout << "After sort: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // Remove duplicates
    auto last = unique(data.begin(), data.end());
    data.erase(last, data.end());
    cout << "After removing duplicates: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // Insert element in middle
    int middle = data.size() / 2;
    data.insert(data.begin() + middle, 99);
    cout << "After inserting 99 at middle: ";
    for (int n : data) cout << n << " ";
    cout << endl;
    
    // Find element
    auto pos = find(data.begin(), data.end(), 99);
    if (pos != data.end()) {
        data.erase(pos);
        cout << "After removing 99: ";
        for (int n : data) cout << n << " ";
    }
    cout << endl;
    
    // Final statistics
    cout << "Final size: " << data.size() << endl;
    cout << "Is empty? " << (data.empty() ? "Yes" : "No") << endl;
}

// ==================== MAIN FUNCTION ====================
int main() {
    srand(time(nullptr));  // Seed random number generator
    
    cout << "===== C++ VECTOR OPERATIONS CHEAT SHEET =====\n" << endl;
    
    // Run all demos
    demoSizeEmpty();
    demoInsert();
    demoRemove();
    demoSortUnsort();
    demoFindSearch();
    demoDedupUniquify();
    demoTraverse();
    comprehensiveExample();
    
    cout << "\n===== END OF DEMONSTRATION =====" << endl;
    
    return 0;
}