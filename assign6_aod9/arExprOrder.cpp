// File Name: arExprOrder.cpp
//
// Author: Andrew Daly
// Date: 04/29/2020
// Assignment Number: 6
// CS 2308.252 Spring 2020
// Instructor: Vladyslav Prokopenko
//
// This program is to use stack data structure 
// that evaluates a generic arithmetic expression

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool checkIfSequenceValid(string seq);

int main() {

    stack<int> myStack;

    string userInput;
    cin >> userInput;

    // printSubexpressions(userInput);
    bool valid = checkIfSequenceValid(userInput);
    cout << (valid ? userInput : "Invalid expression");

    return 0;
}

//Function Definitions:

//***********************************************************
// checkIfSequenceValid: read the expression and pop out
//                       subexpression inside the parentheses
// seq -   an arithmetic expression string to be read
// return: the arithmetic expression itself if the parentheses
//         are balanced, else, an error message.
//***********************************************************

bool checkIfSequenceValid(string seq) {
    stack<int> myStack;
    bool valid = true;
    for (int i = 0; i < seq.length(); ++i) {
        int length = 0;
        if (seq[i] == '(' || seq[i] == '[' || seq[i] == '{') {
            myStack.push(i);
        }
        else if (seq[i] == ')' || seq[i] == ']' || seq[i] == '}') {
            if (myStack.empty()) {
                valid = false;
                break;
            }
            char top = (seq[myStack.top()]);
            if ((seq[i] == ')' && top == '(') || (seq[i] == ']' && top == '[') || (seq[i] == '}' && top == '{')) {
                length = (i - 1) - myStack.top();
                cout << seq.substr(myStack.top() + 1, length) << endl;
                myStack.pop();
            }
            else {
                valid = false;
                break;
            }
        }
    }
    return valid;
}
