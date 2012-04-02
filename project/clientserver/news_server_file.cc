#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"
#include "db_file.h"
#include "protocol/protocol.h"
#include "protocol/com_list_ng_packet.h"
#include "protocol/com_create_ng_packet.h"
#include "protocol/com_delete_ng_packet.h"
#include "protocol/com_list_art_packet.h"
#include "protocol/com_create_art_packet.h"
#include "protocol/com_delete_art_packet.h"
#include "protocol/com_get_art_packet.h"
#include "protocol/ans_list_ng_packet.h"
#include "protocol/ans_create_ng_packet.h"
#include "protocol/ans_delete_ng_packet.h"
#include "protocol/ans_list_art_packet.h"
#include "protocol/ans_create_art_packet.h"
#include "protocol/ans_delete_art_packet.h"
#include "protocol/ans_get_art_packet.h"

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
	
	DBFile db;
	while (true) {
		Connection* conn = server.waitForActivity();
		if (conn != 0) {
			try {
				size_t cmd = MessageHandler::read_cmd(conn);
				switch (cmd) {
				case Protocol::COM_LIST_NG: {
					ComListNgPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					AnsListNgPacket ans;
					ans.ngs = db.list_ng();
					ans.write(conn);
					break;
				}
				case Protocol::COM_CREATE_NG: {
					ComCreateNgPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					size_t res = db.create_ng(com.name);
					AnsCreateNgPacket ans;
					if (res == Protocol::ANS_ACK) {
						ans.ans = res;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res;
					}
					ans.write(conn);
					break;
				}
				case Protocol::COM_DELETE_NG: {
					ComDeleteNgPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					size_t res = db.delete_ng(com.id);
					AnsDeleteNgPacket ans;
					if(res == Protocol::ANS_ACK) {
						ans.ans = res;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res;
					}
					ans.write(conn);
					break;
				}
				case Protocol::COM_LIST_ART: {
					ComListArtPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
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
					break;
				}
				case Protocol::COM_CREATE_ART: {
					ComCreateArtPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					AnsCreateArtPacket ans;
					size_t res = db.create_art(com.ng_id, com.title, com.author, com.text);
					if(res == Protocol::ANS_ACK) {
						ans.ans = res;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res;
					}
					ans.write(conn);
					break;
				}
				case Protocol::COM_DELETE_ART: {
					ComDeleteArtPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					AnsDeleteArtPacket ans;
					size_t res = db.delete_art(com.ng_id, com.art_id);
					if(res == Protocol::ANS_ACK) {
						ans.ans = res;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res;
					}
					ans.write(conn);
					break;
				}
				case Protocol::COM_GET_ART: {
					ComGetArtPacket com;
					if (!com.read(conn)) {
						throw ConnectionClosedException();
					}
					AnsGetArtPacket ans;
					pair<size_t, Article> res = db.get_art(com.ng_id, com.art_id);
					if(res.first == Protocol::ANS_ACK) {
						ans.ans = res.first;
						ans.a = res.second;
					} else {
						ans.ans = Protocol::ANS_NAK;
						ans.err = res.first;
					}
					ans.write(conn);
					break;
				}
				default:
					throw ConnectionClosedException();
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

