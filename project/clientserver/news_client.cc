#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"

#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;
using namespace client_server;
using namespace news_server;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: news_client host-name port-number" << endl;
		exit(1);
	}
	
	Connection conn(argv[1], atoi(argv[2]));
	if (! conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	
	cout << "Type a number: ";
	int nbr;
	while (cin >> nbr) {
		try {
			MessageHandler::write_num(&conn, nbr);
			string answer = MessageHandler::read_str(&conn);
			cout << nbr << " is " << answer << endl;
			cout << "Type another number: ";
		} 
		catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}
