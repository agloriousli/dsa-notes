#ifndef EXPRESSION_EVALUATION_HPP
#define EXPRESSION_EVALUATION_HPP

#include "Stack.hpp"
#include <cctype>
#include <cstring>
#include <cmath>

// Operator precedence table
// Determines how operators compare: '>' = pop from stack, '<' = push to stack, '~' = match parens
const int N_OPTR = 9; // Number of operators
const char pri[N_OPTR][N_OPTR] = { 
   // Operator precedence [stack top][current operator]
   /* +- */ '>', '>', '<', '<', '<', '<', '<', '>', '>',
   /* -  */ '>', '>', '<', '<', '<', '<', '<', '>', '>', 
   /* *  */ '>', '>', '>', '>', '<', '<', '<', '>', '>', 
   /* /  */ '>', '>', '>', '>', '<', '<', '<', '>', '>', 
   /* ^  */ '>', '>', '>', '>', '>', '<', '<', '>', '>', 
   /* !  */ '>', '>', '>', '>', '>', '>', ' ', '>', '>', 
   /* (  */ '<', '<', '<', '<', '<', '<', '<', '~', ' ', 
   /* )  */ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', // Padding
   /* \\0 */ '<', '<', '<', '<', '<', '<', '<', ' ', '~'
   //        +    -    *    /    ^    !    (    )    \\0
   //        |----------- Current operator -----------|
};

// Helper function: read number from expression string
// Handles both integers and decimal floating point numbers
void readNumber( char* &S, Stack<double>& opnd ) {
   double num = 0.0;
   while ( isdigit(*S) ) { // Read integer part
      num = num * 10 + (*S - '0');
      S++;
   }
   if ( *S == '.' ) { // Handle decimal part
      S++;
      double fraction = 0.1;
      while ( isdigit(*S) ) {
         num += (*S - '0') * fraction;
         fraction *= 0.1;
         S++;
      }
   }
   opnd.push(num); // Push completed number onto operand stack
}

// Helper function: binary operation calculation
// Performs one of five binary operations: +, -, *, /, ^
double calcu( double a, char op, double b ) {
   switch ( op ) {
      case '+': return a + b;
      case '-': return a - b;
      case '*': return a * b;
      case '/': return a / b;
      case '^': return pow(a, b); // Exponentiation
      default: return 0.0;
   }
}

// Helper function: unary operation calculation
// Currently supports factorial (!)
double calcu( double a, char op ) {
   switch ( op ) {
      case '!': { // Factorial operation
         int result = 1;
         for ( int i = 1; i <= (int)a; i++ ) result *= i;
         return result;
      }
      default: return a;
   }
}

// Main expression evaluation algorithm using operator precedence parsing
// Handles infix expressions with proper operator precedence and associativity
double evaluate( char* S, char* RPN = nullptr ) {
   // S is guaranteed to be syntactically correct
   Stack<double> opnd; // Operand stack
   Stack<char> optr; // Operator stack
   
   optr.push('\0'); // Sentinel for bottom of stack
   while ( !optr.empty() ) { // Process all characters until operator stack empty
      if ( isdigit( *S ) ) { // Current character is a number (possibly multi-digit, decimal)
         readNumber( S, opnd ); // Parse and push to operand stack
         if ( RPN ) {
            // append( RPN, opnd.top() ); // Can append to RPN string
         }
      }
      else { // Current character is an operator
         switch( pri[optr.top()][*S] ) { // Compare with top of operator stack
            case '<': 
               optr.push( *S ); // Precedence is lower: push current operator
               S++; 
               break;
            case '>': { // Precedence is higher: pop and compute
               char op = optr.pop();
               if ( op == '!' ) { // Unary operator
                  double a = opnd.pop();
                  opnd.push( calcu( a, op ) );
               } else { // Binary operator
                  double b = opnd.pop();
                  double a = opnd.pop();
                  opnd.push( calcu( a, op, b ) );
               }
               if ( RPN ) {
                  // append( RPN, op ); // Can append operator to RPN string
               }
               break;
            }
            case '~': 
               optr.pop(); // Matching pair of parens: just pop
               S++; 
               break;
            case ' ': 
               // Error case - should not happen for valid expressions
               break;
         }
      }
   }
   return opnd.pop(); // Pop and return final result
} // evaluate

// RPN (Reverse Polish Notation) expression evaluation
// Evaluates expressions in postfix notation where operators follow operands
double rpn( char* S ) { // Evaluate RPN expression
   Stack<double> opnd; // Only need operand stack for RPN
   char* item = strtok( S, " " ); // Parse space-separated tokens
   
   while ( item ) {
      if ( 1 < strlen( item ) || isdigit( item[0] ) ) { // Token is an operand
         opnd.push( atof( item ) ); // Push to operand stack
      }
      else { // Token is an operator
         if ( item[0] == '!' ) { // Unary operator
            double a = opnd.pop();
            opnd.push( calcu( a, item[0] ) );
         } else { // Binary operator
            double b = opnd.pop(); // Pop right operand first
            double a = opnd.pop(); // Then left operand
            opnd.push( calcu( a, item[0], b ) );
         }
      }
      item = strtok( NULL, " "); // Get next token
   }
   return opnd.pop(); // Last remaining value is the result
} // rpn

#endif // EXPRESSION_EVALUATION_HPP