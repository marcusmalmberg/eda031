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

# Dependencies, the implicit rule .cc => .o is used
string_test.o: string_test.cc
