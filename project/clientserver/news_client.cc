#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"
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
#include <algorithm>

using namespace std;
using namespace client_server;
using namespace news_server;
using namespace protocol;

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
	
	string cmd;
	while (cin >> cmd) {
		try {
			if (cmd == "list") {
				cin >> cmd;
				if (cmd != "ngs") {    // LIST_ART
					cout << "Listing articles for ng=" << cmd << ":" << endl;
					size_t id = atoi(cmd.c_str());
					ComListArtPacket com;
					com.id = id;
					com.write(&conn);
					AnsListArtPacket ans;
					MessageHandler::read_cmd(&conn);
					ans.read(&conn);
					for_each(ans.arts.begin(), ans.arts.end(), [] (Article a) {
						cout << a.id << ". " << a.title << " From: " << a.author << endl;
					});
				} else { 	// LIST_NG
					cout << "Listing newsgroups:" << endl;
					ComListNgPacket com;
					com.write(&conn);
					AnsListNgPacket ans;
					MessageHandler::read_cmd(&conn);
					ans.read(&conn);
					for_each(ans.ngs.begin(), ans.ngs.end(), [] (Newsgroup ng) {
						cout << ng.id << ". " << ng.name << endl;
					});
				}
			} else if (cmd == "read") {		// GET_ART
				// TODO: Implement
			} else if (cmd == "create") {
				if (cin >> cmd) {
					if (cmd == "ng") {		// CREATE_NG
						string name;
						cin >> name;
						ComCreateNgPacket com;
						com.name = name;
						com.write(&conn);
						AnsCreateNgPacket ans;
						MessageHandler::read_cmd(&conn);
						ans.read(&conn);
					} else {		// CREATE_ART
						// TODO: Implement..
					}
				}
			} else if (cmd == "delete") {
				if (cin >> cmd) {
					if (cmd == "ng") {		// DELET_NG
						// TODO: Implement..
						size_t id;
						cin >> id;
						ComDeleteNgPacket com;
						com.id = id;
					} else {		// DELETE_ART
						// TODO: Implement..
					}
				}
			} else if (cmd == "quit") {
				break;
			}
		} catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}
