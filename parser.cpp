/*
 *  parser.cpp
 *  Sandra Ortellado
 *  10/16/22
 *
 *  CS 15 Project 1 Part 2
 *
 *  Purpose: Define parseRString function
 *
 */

#include <string> 
#include <vector>
#include <iostream>

using namespace std;

/* parseRString
 * Purpose: Reads input from istream until all curly braces are matched 
 * or until it reaches the end of the input
 * Parameters: istream
 * Returns: rstring from istream
 */
string parseRString(istream &input) {
    vector<string> stack;
    string s = "";
    string final_string = "{";
    stack.push_back("{");
    while (!stack.empty()) {
        input >> s;
        if (s == "{" || s == "}") {
            if (s == "}") {
                stack.pop_back();
                final_string += " }";
            } else {
                final_string += " " + s;
                stack.push_back(s);
            }
        } else {
            final_string += " " + s;
        }
    }
    return final_string;
}
