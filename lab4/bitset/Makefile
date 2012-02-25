#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

debug: CXX += -DDEBUG -ggdb
debug: CC += -DDEBUG -ggdb
debug: nameserver_test

# Linking:
simple_bit_test: simplebitsettest.o simplebitset.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
simplebitsettest.o: simplebitsettest.cc simplebitset.h
simplebitset.o: simplebitset.h
