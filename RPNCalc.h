/*
 *  RPNCalc.h
 *  Sandra Ortellado
 *  10/16/22
 *
 *  CS 15 Project 1 Part 2
 *
 *  Purpose: Header file for RPNCalc class
 *
 */


#ifndef RPNCALC_H
#define RPNCALC_H

#include <string>
#include "DatumStack.h"

class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    void run();

private:
    DatumStack stack;
    Datum int_operation(string input);
    Datum bool_operation(string input);
    bool is_number(string input);
    void process_command(string input);
    void parseR_test(istream &input);
};

#endif
