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

# Dependencies, the implicit rule .cc => .o is used
string_test.o: string_test.cc

date_test.o: date_test.cc date.h
date.o: date.h

