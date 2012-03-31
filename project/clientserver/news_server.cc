#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
using namespace client_server;
using namespace news_server;


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
	
	while (true) {
		Connection* conn = server.waitForActivity();
		if (conn != 0) {
			try {
				MessageHandler::read_num(conn);
				MessageHandler::write_str(conn, "HEJ!");
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

