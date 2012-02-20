#
# Makefile for CPP
#

# Compiler and compiler options:
CXX       = g++
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
SRC		  = $(wildcard *.cc)
OBJS	  = $(SRC:.cc=.o)
DEPS	  = $(SRC:.cc=.d)
PREFIX	  = ~/eda031/usr

.PHONY: all
all: ltest

.PHONY: clean
clean:
	$(RM) $(OBJS)

.PHONY: install
install: all
	install -t $(PREFIX)/bin ltest

.PHONY: uninstall
uninstall:
	$(RM) $(PREFIX)/bin/ltest

include $(DEPS)

%.d: %.cc
	@set -e; rm -f $@; \
	$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

# Linking:
ltest: ltest.o list.o
	$(CXX) -o $@ $^

graph_test: graph_test.o vertex.o vertexlist.o
	$(CXX) -o $@ $^

topsort: topsort.o vertex.o vertexlist.o
	$(CXX) -o $@ $^

# Dependencies, the implicit rule .cc => .o is used
ltest.o: ltest.cc list.h
list.o: list.cc list.h
graph_test.o: graph.h vertex.h vertexlist.h
topsort.o: topsort.cc
vertex.o: vertex.h
vertexlist.o: vertex.h vertexlist.h
