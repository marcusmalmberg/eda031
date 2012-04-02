#
# Makefile to make the file libclientserver.a, containing
# connection.o and server.o
#

CXX			 = g++
CXXFLAGS	 = -ggdb  -Wall -W -Werror -pedantic-errors
CXXFLAGS	+= -Wmissing-braces -Wparentheses -std=c++0x
# The following option cannot be used since some of the socket
# macros give warnings on "old-style-cast"
#CXXFLAGS	+= -Wold-style-cast

SRC	= $(wildcard *.cc)

.PHONY: all lib clean cleaner

all: lib news_server_memory news_server_file news_client

lib: libclientserver.a libprotocol.a

news_server_memory: news_server_memory.o message_handler.o db_memory.o
	$(CXX) -o ../bin/$@ $^ -L. -lclientserver -lprotocol

news_server_file: news_server_file.o message_handler.o db_file.o
	$(CXX) -o ../bin/$@ $^ -L. -lclientserver -lprotocol

news_client: news_client.o message_handler.o
	$(CXX) -o ../bin/$@ $^ -L. -lclientserver -lprotocol

# Create the library; ranlib is for Darwin and maybe other systems.
# Doesn't seem to do any damage on other systems.

libclientserver.a: connection.o server.o
	ar rv libclientserver.a \
	connection.o server.o
	ranlib libclientserver.a

libprotocol.a: protocol/protocol.o protocol/com_list_ng_packet.o protocol/com_create_ng_packet.o protocol/com_delete_ng_packet.o protocol/com_list_art_packet.o protocol/com_create_art_packet.o protocol/com_delete_art_packet.o protocol/com_get_art_packet.o protocol/ans_list_ng_packet.o protocol/ans_create_ng_packet.o protocol/ans_delete_ng_packet.o protocol/ans_list_art_packet.o protocol/ans_create_art_packet.o protocol/ans_delete_art_packet.o protocol/ans_get_art_packet.o
	ar rv libprotocol.a \
	protocol/protocol.o \
	protocol/com_list_ng_packet.o \
	protocol/com_create_ng_packet.o \
	protocol/com_delete_ng_packet.o \
	protocol/com_list_art_packet.o \
	protocol/com_create_art_packet.o \
	protocol/com_delete_art_packet.o \
	protocol/com_get_art_packet.o \
	protocol/ans_list_ng_packet.o \
	protocol/ans_create_ng_packet.o \
	protocol/ans_delete_ng_packet.o \
	protocol/ans_list_art_packet.o \
	protocol/ans_create_art_packet.o \
	protocol/ans_delete_art_packet.o \
	protocol/ans_get_art_packet.o
	ranlib libprotocol.a

clean:
	$(RM) *.o

reset_db: 
	$(RM) -r db

cleaner: clean reset_db
	$(RM) libclientserver.a
	$(RM) libprotocol.a
	$(RM) *.d *.d.*

%.d: %.cc
	@set -e; rm -f $@; \
	 $(CXX) -MM $(CXXFLAGS) $< > $@.$$$$; \
	 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	 rm -f $@.$$$$

include $(SRC:.cc=.d)
