#README

A) Title and Author
Title: Project 1 CalcYouLater Part 1
Author: Sandra Ortellado

B) Purpose
Build program for RPN calculation.

C) Help Received
Referenced Makefile and Stack topics on Canvas.

D) Files Provided:

* DatumStack.h - Header file defining DatumStack class
* DatumStack.cpp - Define all member functions of the DatumStack class
* DatumStack_tests.cpp - Unit testing file for DatumStack member functions
                         and parseRstring function
* parser.cpp - Define parseRString function
* parser.h - Header file for parseRstring function
* Makefile - Provides rules for compiling and linking all files
* main.cpp - Runs the program
* RPNCalc.h - Header file for RPNCalc class
* RPNCalc.cpp - Define all member functions of the RPNCalc class
* README.md - Explains program

F) Data Structures

Mainly worked with stacks to implement the DatumStack class that will hold
Datum objects and the parseRstring function. It was part of the sspecification
for the DatumStack class, and I chose to use it for parseRstring to optimally 
match up pairs of brackets. Two other problems it can be used to solve are
Depth First Search and reversing a string.

G) Testing Plan

The DatumStack_tests.cpp file contains two functions that test 1) all the
DatumStack member functions and 2) the parseRstring function by asserting
expected results and attempting to account for edge cases.