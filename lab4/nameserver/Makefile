#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

# Linking:
vec: VectorNameServer.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
VectorNameServer.o: VectorNameServer.h nameserverinterface.h
