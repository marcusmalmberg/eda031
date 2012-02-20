# Define the compiler options
CXXFLAGS  = -pipe -O2 -Wall -W -ansi -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast

# Define what to do when make is executed without arguments.
all: ltest

# The following rule means "if ltest is older than ltest.o or list.o,
# then link ltest".
ltest: ltest.o list.o
	g++ -o ltest ltest.o list.o

# Define the rules for the object files.
ltest.o: ltest.cc list.h
	g++ -c $(CXXFLAGS) ltest.cc
list.o: list.cc list.h
	g++ -c $(CXXFLAGS) list.cc

coding.o: coding.cc coding.h
	g++ -c $(CXXFLAGS) coding.cc

encode: encode.o coding.o
	g++ -o encode encode.o coding.o

encode.o: encode.cc coding.h
	g++ -c $(CXXFLAGS) encode.cc

decode: decode.o coding.o
	g++ -o decode decode.o coding.o
	
decode.o: decode.cc coding.h
	g++ -c $(CXXFLAGS) decode.cc
