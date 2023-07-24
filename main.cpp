/*
 * main.cpp
 * Sandra Ortellado
 * 10/16/22
 * CS 15 Project 1 Part 2
 * 
 * Purpose: main function to run program
 *
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "RPNCalc.h"

using namespace std;

int main() {
    RPNCalc calc = RPNCalc();
    calc.run();
}
