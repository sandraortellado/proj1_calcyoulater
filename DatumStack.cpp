/*
 * DatumStack.cpp
 * Sandra Ortellado
 * 10/9/22
 * CS 15 Project 1 Part 2
 * 
 * Purpose: Define all member functions of the DatumStack class
 *
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "DatumStack.h"

using namespace std;

//Default constructor takes no parameters and initializes an empty stack
DatumStack::DatumStack() {
}

//Second constructor takes an array of Datum and an integer specifying 
//the size of the array as parameters and creates a stack
//so that the elements of the array are on the stack 
//with the array’s element 0 pushed on first
DatumStack::DatumStack(Datum *d, int size) {
    dVec = vector<Datum>();
    for (int i = 0; i < size; i++) {
        dVec.push_back(d[i]);
    }
}

//Destructor
DatumStack::~DatumStack() {

}

/* isEmpty
 * Purpose: Determine if the stack is empty
 * Parameters: none
 * Returns: boolean true or false
 */
bool DatumStack::isEmpty() {
    return dVec.empty();
}

/* clear
 * Purpose: Makes the stack vector into an empty vector
 * Parameters: none
 * Returns: nothing
 */
void DatumStack::clear() {
    dVec.clear(); 
}

/* size
 * Purpose: Determines the number of elements in the stack
 * Parameters: none
 * Returns: an integer value that is the number of elements in the stack
 */
int DatumStack::size() {
    return dVec.size();
}

/* top
 * Purpose: Returns the top Datum element on the stack, without removing
 * Parameters: none
 * Returns: the top Datum element on the stack
 */
Datum DatumStack::top() {
    if (this->isEmpty()) {
        throw runtime_error("empty_stack");
    }
    return dVec.back();
}

/* top
 * Purpose: Removes the top element on the stack, without returning
 * Parameters: none
 * Returns: nothing
 */
void DatumStack::pop() {
    if (this->isEmpty()) {
        throw runtime_error("empty_stack");
        return;
    }
    dVec.pop_back();
}

void DatumStack::push(Datum &d) {
    dVec.push_back(d);
}

