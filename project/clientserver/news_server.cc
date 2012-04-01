#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"
#include "db_memory.h"
#include "protocol/protocol.h"
#include "protocol/com_list_ng_packet.h"
#include "protocol/com_create_ng_packet.h"
#include "protocol/com_list_art_packet.h"
#include "protocol/ans_list_ng_packet.h"
#include "protocol/ans_create_ng_packet.h"
#include "protocol/ans_list_art_packet.h"

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
				switch (cmd) {
				case Protocol::COM_LIST_NG: {
					cout << "Requesting COM_LIST_NG." << endl;
					ComListNgPacket com;
					com.read(conn);
					AnsListNgPacket ans;
					ans.ngs = db.list_ng();
					ans.write(conn);
					cout << "Answer sent." << endl;
					break;
				}
				case Protocol::COM_CREATE_NG: {
					cout << "Requesting COM_CREATE_NG." << endl;
					ComCreateNgPacket com;
					com.read(conn);
					size_t res = db.create_ng(com.name);
					AnsCreateNgPacket ans;
					if (res == Protocol::ANS_ACK) {
						ans.ans = res;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res;
					}
					ans.write(conn);
					cout << "Answer sent." << endl;
					break;
				}
				case Protocol::COM_DELETE_NG: {
					//TODO: Implement
				}
				case Protocol::COM_LIST_ART: {
					cout << "Requesting COM_LIST_ART." << endl;
					ComListArtPacket com;
					com.read(conn);
					AnsListArtPacket ans;
					pair<size_t, vector<Article>> p = db.list_art(com.id);
					if (p.first == Protocol::ANS_ACK) {
						ans.ans = p.first;
						ans.arts = p.second;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = p.first;
					}
					ans.write(conn);
					cout << "Answer sent." << endl;
					break;
				}
				case Protocol::COM_CREATE_ART: {
					//TODO: Implement
				}
				case Protocol::COM_DELETE_ART: {
					//TODO: Implement
				}
				case Protocol::COM_GET_ART: {
					//TODO: Implement
				}
				default:
					break;
				}
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

