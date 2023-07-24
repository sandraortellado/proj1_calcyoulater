/*
 * RPNCalc.cpp
 * Sandra Ortellado
 * 10/16/22
 * CS 15 Project 1 Part 2
 * 
 * Purpose: Define all member functions of the RPNCalc class
 *
 */

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "RPNCalc.h"
#include "parser.h"

using namespace std;

//Default constructor takes no parameters and initializes RPNCalc object
RPNCalc::RPNCalc() {
    stack = DatumStack();
}

//Destructor
RPNCalc::~RPNCalc() {
   
}

/* run
 * Purpose: Reads in commands from standard input
 * Parameters: none
 * Returns: nothing
 */
void RPNCalc::run() {
    string input;
    while (cin >> input) {
        try {
            process_command(input);
        } catch (runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
        } catch (...) {
            cout << "A DIFFERENT ERROR OCCURRED" << endl;
        }
        if (input == "quit") {
            break;
        }
    }
    stack.clear();
    cerr << "Thank you for using CalcYouLater.\n";
}

/* int_operation
 * Purpose: Helper function to execute operations for int
 * Parameters: string input
 * Returns: Datum of result of operation
 */
Datum RPNCalc::int_operation(string input) {
    Datum onTop = stack.top();
    stack.pop();
    Datum secondFromTop = stack.top();
    stack.pop();
    int operated = onTop.getInt();
    int operand = secondFromTop.getInt();
    int result;
    if (input == "+") {
        result = operand + operated;
    } else if (input == "-") {
        result = operand - operated;
    } else if (input == "*") {
        result = operand * operated;
    } else if (input == "/") {
        result = operand / operated;
    } else if (input == "mode") {
        result = operand % operated;
    }
    return Datum(result);
}

/* bool_operation
 * Purpose: Helper function to execute operations for boolean
 * Parameters: string input
 * Returns: Datum of result of operation
 */
Datum RPNCalc::bool_operation(string input) {
    Datum onTop = stack.top();
    stack.pop();
    Datum secondFromTop = stack.top();
    stack.pop();
    if (input == "==") {
        if (onTop.isRString() && !secondFromTop.isRString()) {
            return Datum(false);
        } else if (onTop.isInt() && !secondFromTop.isInt()) {
            return Datum(false);
        } else if (onTop.isBool() && !secondFromTop.isBool()) {
            return Datum(false);
        }
    }

    int operated = onTop.getInt();
    int operand = secondFromTop.getInt();
    
    bool result;
    if (input == ">") {
        result = operand > operated;
    } else if (input == "<") {
         result = operand < operated;
    } else if (input == ">=") {
        result = operand >= operated;
    } else if (input == "<=") {
         result = operand <= operated;
    } else if (input == "==") {
        result = operand == operated;
    }
    return Datum(result);
}

/* is_number
 * Purpose: Helper function to determine if input is a number
 * Parameters: string input
 * Returns: Boolean if input is a number
 */
bool RPNCalc::is_number(string input) {
    // Found this on stack overflow
    char *p;
    strtol(input.c_str(), &p, 10);
    return *p == 0;
}

/* process_command
 * Purpose: Function to recognize command from input and execute accordingly
 * Parameters: string input
 * Returns: Nothing
 */
void RPNCalc::process_command(string input) {
    if (input == "quit") {
        return;
    }
    if (is_number(input)) {
        int num = stoi(input);
        Datum dn = Datum(num);
        stack.push(dn);
    } else if (input == "#t") {
        Datum bd = Datum(true);
        stack.push(bd);
    } else if (input == "#f") {
        Datum bd = Datum(false);
        stack.push(bd);
    } else if (input == "not") { 
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum top = stack.top();
        stack.pop();
        bool b = top.getBool();
        Datum nb = Datum(!b);
        stack.push(nb);
    } else if (input == "print") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        cout << stack.top().toString() << endl;
    } else if (input == "clear") {
        stack.clear();
    } else if (input == "drop") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        stack.pop();
    } else if (input == "dup") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum copy = stack.top();
        stack.push(copy);
    } else if (input == "swap") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum old_top = stack.top();
        stack.pop();
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum new_top = stack.top();
        stack.pop();
        stack.push(old_top);
        stack.push(new_top);
    } else if (input == "+" || input == "-" || input == "*" || input == "/" || input == "mod") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        if (input == "/") {
            Datum onTop = stack.top();
            stack.pop();
            Datum secondFromTop = stack.top();
            stack.pop();
            if (onTop.isInt() && onTop.getInt() == 0) {
                cerr << "Error: division by 0.\n";
                return;
            }
            stack.push(secondFromTop);
            stack.push(onTop);
        }
        Datum result = int_operation(input);
        stack.push(result);
    } else if (input == "<" || input == ">" || input == "<=" || input == ">=" || input == "==") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum result = bool_operation(input);
        stack.push(result);
    } else if (input == "{") {
        string string_res = parseRString(cin);
        Datum rstring = Datum(string_res);
        stack.push(rstring);
    } else if (input == "exec") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        if (!stack.top().isRString()) {
            cerr << "Error: cannot execute non rstring\n";
            return;
        } 
        Datum dtop = stack.top();
        stack.pop();
        string top = dtop.getRString();
        istringstream iss (top);
        string s;
        iss >> s;
        while (iss >> s) {
            if (s == "{") {
                string string_res = parseRString(iss);
                Datum rstring = Datum(string_res);
                stack.push(rstring);
            } else {
                try {
                    process_command(s);
                    if (input == "quit") {
                        return;
                    }
                } catch (runtime_error& e) {
                    cerr << "Error: " << e.what() << endl;
                    return;
                } catch (...) {
                    cout << "A DIFFERENT ERROR OCCURRED" << endl;
                    return;
                }
            }
        }
    } else if (input == "file") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        if (!stack.top().isRString()) {
            cerr << "Error: file operand not rstring\n";
            return;
        }
        string myText;
        Datum file = stack.top();
        stack.pop();
        string filename = file.toString();
        filename = filename.substr(1, filename.length() - 2);
        filename = filename.substr(1, filename.length() - 2);
        ifstream MyReadFile;
        MyReadFile.open(filename);

        if (MyReadFile.fail()) {
            cerr << "Unable to read " << filename << "\n";
            return;
        }
        string readfile;
        MyReadFile >> readfile;

        while (!MyReadFile.eof()) {
            if (readfile == "{") {
                string string_res = parseRString(MyReadFile);
                Datum rstring = Datum(string_res);
                stack.push(rstring);
            } else {
                try {
                    process_command(readfile);
                } catch (runtime_error& e) {
                    cerr << "Error: " << e.what() << endl;
                } catch (...) {
                    cout << "A DIFFERENT ERROR OCCURRED" << endl;
                }
            }
            MyReadFile >> readfile;
        }

        MyReadFile.close();
    } else if (input == "if") {
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum if_false = stack.top();
        if (!if_false.isRString()) {
            cerr << "Error: expected rstring in if branch\n";
            return;
        }
        stack.pop();
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum if_true = stack.top();
        if (!if_true.isRString()) {
            cerr << "Error: expected rstring in if branch\n";
            return;
        }
        stack.pop();
        if (stack.isEmpty()) {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum conditionD = stack.top();
        stack.pop();
        if (!conditionD.isBool()) {
            cerr << "Error: expected boolean in if test\n";
            return;
        }
        bool condition = conditionD.getBool();

        if (condition) {
            stack.push(if_true);
        } else {
            stack.push(if_false);
        }

        try {
            process_command("exec");
        } catch (runtime_error& e) {
            cerr << "Error: " << e.what() << endl;
            return;
        } catch (...) {
            cout << "A DIFFERENT ERROR OCCURRED" << endl;
            return;
        }
    } else if (input == "}") {
        return;
    } else {
        cerr << input << ": unimplemented\n";
        return;
    }
}

/* parseR_test
 * Purpose: Helper function to determine if input is a number
 * Parameters: string input
 * Returns: Boolean if input is a number
 */
void RPNCalc::parseR_test(istream &input) {
    string s;
    input >> s;
}