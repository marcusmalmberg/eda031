#
# Makefile for C++ Programming, exercise 1
# Execute 'make' ('gmake' on EFD) to compile and link all programs,
# or 'make progname', to compile and link 'progname'
#

# Compiler and linker
CXX     = g++
CC      = g++

# Preprocessor, compiler and linker options
CXXFLAGS  = -pipe -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CXXFLAGS += -ggdb
LDFLAGS  = -ggdb

# Source files
SRC	= $(wildcard *.cc)
OBJ	= $(SRC:.cc=.o)

# Executables -- list all executable programs here 
PROGS	= hello datetest sizetest palindrome

all: $(PROGS)

# Object files needed to link the executables
hello: hello.o
datetest: datetest.o date.o
sizetest: sizetest.o date.o
palindrome: palindrome.o

.phony:	all clean cleaner

clean:
	$(RM) *.o

cleaner: clean
	$(RM) $(PROGS)

# Generate and include dependencies
%.d: %.cc
	@set -e; rm -f $@; \
	$(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SRC:.cc=.d)
