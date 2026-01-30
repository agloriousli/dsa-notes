#ifndef STACK_SHUFFLE_HPP
#define STACK_SHUFFLE_HPP

// Stack shuffle implementation showing parenthesis matching correspondence
// Every stack shuffle corresponds to a sequence of n push (A) and n pop (B) operations
// In any prefix, the number of pushes must be >= pops (valid parenthesis rule)

#include <iostream>
#include <stack>
#include <vector>

// Concrete example demonstrating stack shuffle
// Sequence: A1, A2, A3, B3, B2, A4, B4, B1 corresponds to ((( ) ) ( ) )
void stackShuffleExample() {
    std::stack<int> S;
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<int> output;
    
    // A1: push 1 (left paren)
    S.push(1);
    std::cout << "A1 pushed ( - push 1, S.size = " << S.size() << std::endl;
    
    // A2: push 2 (left paren)
    S.push(2);
    std::cout << "A2 pushed ( - push 2, S.size = " << S.size() << std::endl;
    
    // A3: push 3 (left paren)
    S.push(3);
    std::cout << "A3 pushed ( - push 3, S.size = " << S.size() << std::endl;
    
    // B3: pop 3 (right paren)
    output.push_back(S.top());
    S.pop();
    std::cout << "B3 popped ) - pop 3, S.size = " << S.size() << std::endl;
    
    // B2: pop 2 (right paren)
    output.push_back(S.top());
    S.pop();
    std::cout << "B2 popped ) - pop 2, S.size = " << S.size() << std::endl;
    
    // A4: push 4 (left paren)
    S.push(4);
    std::cout << "A4 pushed ( - push 4, S.size = " << S.size() << std::endl;
    
    // B4: pop 4 (right paren)
    output.push_back(S.top());
    S.pop();
    std::cout << "B4 popped ) - pop 4, S.size = " << S.size() << std::endl;
    
    // B1: pop 1 (right paren)
    output.push_back(S.top());
    S.pop();
    std::cout << "B1 popped ) - pop 1, S.size = " << S.size() << std::endl;
    
    std::cout << "Output sequence: ";
    for (int num : output) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Convert stack shuffle operation sequence to parenthesis string
// Maps 'A' operations (push) to '(' and 'B' operations (pop) to ')'
std::string stackShuffleToParenthesis(const std::vector<char>& operations) {
    std::string result;
    int stackSize = 0;
    
    for (char op : operations) {
        if (op == 'A') {
            result += '('; // Push operation = left parenthesis
            stackSize++;
        } else if (op == 'B') {
            result += ')'; // Pop operation = right parenthesis
            stackSize--;
        }
        // For any valid stack shuffle, stackSize should never go negative
    }
    return result;
}

#endif