###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  Sandra Ortellado

MAKEFLAGS += -L 

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 -g

CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(LDFLAGS) -o CalcYouLater main.o RPNCalc.o DatumStack.o Datum.o parser.o

DatumStack_tests.o: DatumStack_tests.cpp
DatumStack.o: DatumStack.cpp DatumStack.h
parser.o: parser.cpp
RPNCalc.o: RPNCalc.cpp RPNCalc.h
main.o: main.cpp

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)


##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
