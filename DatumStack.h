/*
 *  CharLinkedList.h
 *  Sandra Ortellado
 *  10/9/22
 *
 *  CS 15 Project 1 Part 2
 *
 *  Purpose: Header file defining DatumStack class
 *
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <string>
#include <vector>
#include "Datum.h"

using namespace std;

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum *d, int size);
    ~DatumStack();

    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum &d);

    private:
    vector<Datum> dVec;
};

#endif