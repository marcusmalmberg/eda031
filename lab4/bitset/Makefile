#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

# Linking:
simple_bit_test: simplebitsettest.o simplebitset.o
	$(CXX) -o $@ $^

bit_test: bitsettest1.o bitset.o bitreference.o
	$(CXX) -o $@ $^

bit_iter_test: bitsettest2.o bitset.o bitreference.o bitsetiterator.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
simplebitsettest.o: simplebitsettest.cc simplebitset.h
simplebitset.o: simplebitset.h

bitsettest1.o: bitsettest1.cc
bitsettest2.o: bitsettest2.cc
bitset.o: bitset.h bitreference.h
bitreference.o: bitreference.h bitset.h
bitsetiterator.o: bitsetiterator.h
