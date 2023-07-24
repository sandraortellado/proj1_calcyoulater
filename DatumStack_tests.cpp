/*
 * DatumStack_tests.cpp
 * Sandra Ortellado
 * 10/9/22
 * CS 15 Project 1 Part 2
 * 
 * Purpose: Test Datum Stack and parser functions
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <sstream> 

#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"

void stack_test() {
    DatumStack d1 = DatumStack();
    assert(d1.isEmpty());
    assert(d1.size() == 0);
    Datum el1 = Datum(true);
    Datum el2 = Datum("string");
    d1.push(el1);
    d1.push(el2);
    assert(d1.size() == 2);
    assert(d1.top().toString() == "string");

    Datum dArr[2] = {el1, el2};
    DatumStack d2 = DatumStack(dArr, 2);
    assert(d2.top().toString() == "string");
    assert(d2.size() == 2);
    d2.pop();
    assert(d2.size() == 1);
    assert(d2.top().getBool());
    d2.push(el2);
    d2.clear();
    assert(d2.isEmpty());
}

void parse_test() {

    string s = " 1 { 4 2 } }";
    istringstream iss (s);
    string result = parseRString(iss);
    assert(result == "{ 1 { 4 2 } }");
}

int main() {
    stack_test();
    parse_test();
}