#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"
#include "db_memory.h"
#include "protocol.h"
#include "packet/com_list_ng_packet.h"
#include "packet/com_list_art_packet.h"
#include "packet/ans_list_ng_packet.h"
#include "packet/ans_list_art_packet.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace client_server;
using namespace news_server;
using namespace protocol;

int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: newsserver port-number" << endl;
		exit(1);
	}
	
	Server server(atoi(argv[1]));
	if (! server.isReady()) {
		cerr << "Server initialization error" << endl;
		exit(1);
	}
	
	DBMemory db;
	while (true) {
		Connection* conn = server.waitForActivity();
		if (conn != 0) {
			try {
				size_t cmd = MessageHandler::read_cmd(conn);
				BasePacket* com;
				AnsPacket* ans;
				switch (cmd) {
				case Protocol::COM_LIST_NG:
					com = new ComListNgPacket();
					com->read(conn);
					ans = new AnsListNgPacket();
					(static_cast<AnsListNgPacket*>(ans))->ngs = db.list_ng();
					ans->write(conn);
					break;
				case Protocol::COM_LIST_ART:
					com = new ComListArtPacket();
					com->read(conn);
					ans = new AnsListArtPacket();
					(static_cast<AnsListArtPacket*>(ans))->arts = db.list_art((static_cast<ComListArtPacket*>(com))->id);
					ans->write(conn);
					break;
				default:
					break;
				}
				delete com;
				delete ans;
			}
			catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				delete conn;
				cout << "Client closed connection" << endl;
			}
		}
		else {
			server.registerConnection(new Connection);
			cout << "New client connects" << endl;
		}
	}
}

