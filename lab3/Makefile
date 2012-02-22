#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

# Linking:
string_test: string_test.o
	$(CXX) -o $@ $^

date_test: date_test.o date.o
	$(CXX) -o $@ $^

tostring_test: tostring_test.o tostring.o date.o
	$(CXX) -o $@ $^

string_cast_test: string_cast_test.o string_cast.o date.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
string_test.o: string_test.cc

date_test.o: date_test.cc date.h
date.o: date.cc date.h

tostring_test.o: tostring_test.cc tostring.cc date.h
tostring.o: tostring.cc

string_cast_test.o: string_cast_test.cc string_cast.cc date.h
string_cast.o: string_cast.cc
