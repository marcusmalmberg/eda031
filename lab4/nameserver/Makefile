#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

# Linking:
nameserver_test: nstest.o VectorNameServer.o MapNameServer.o HashNameServer.o
	$(CXX) -o $@ $^

nameserver_time: nstime.o VectorNameServer.o MapNameServer.o HashNameServer.o
	$(CXX) -o $@ $^

vec: VectorNameServer.o
	$(CXX) -o $@ $^

map: MapNameServer.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
VectorNameServer.o: VectorNameServer.h nameserverinterface.h
MapNameServer.o: MapNameServer.h nameserverinterface.h
HashNameServer.o: HashNameServer.h nameserverinterface.h
nstest.o: nstest.cc nameserverinterface.h VectorNameServer.h MapNameServer.h HashNameServer.h
nstime.o: nstime.cc nameserverinterface.h VectorNameServer.h MapNameServer.h HashNameServer.h
