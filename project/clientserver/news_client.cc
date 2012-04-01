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
					cout << "Listing articles for ng with id: " << cmd << endl;
					size_t id = atoi(cmd.c_str());
					ComListArtPacket com;
					com.id = id;
					com.write(&conn);
					AnsListArtPacket ans;
					MessageHandler::read_cmd(&conn);
					ans.read(&conn);
					for_each(ans.arts.begin(), ans.arts.end(), [] (Article a) {
						cout << a.id << ". " << a.title << endl;
					});
				} else { 	// LIST_NG
					cout << "Listing all newsgroups:" << endl;
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
						if(ans.ans == Protocol::ANS_ACK) {
							cout << "Newsgroup created." << endl;
						} else {
							cout << "Error: " << ans.err << endl;
						}
					} else {		// CREATE_ART
						size_t ng_id;
						cin >> ng_id;
						string title;
						cin >> title;
						string author;
						cin >> author;
						string text;
						cin >> text;
						ComCreateArtPacket com;
						com.ng_id = ng_id;
						com.title = title;
						com.author = author;
						com.text = text;
						com.write(&conn);
						AnsCreateArtPacket ans;
						MessageHandler::read_cmd(&conn);
						ans.read(&conn);
						if(ans.ans == Protocol::ANS_ACK) {
							cout << "Article created." << endl;
						} else {
							cout << "Error: " << ans.err << endl;
						}
					}
				}
			} else if (cmd == "delete") {
				if (cin >> cmd) {
					if (cmd == "ng") {		// DELET_NG
						size_t id;
						cin >> id;
						ComDeleteNgPacket com;
						com.id = id;
						com.write(&conn);
						AnsDeleteNgPacket ans;
						MessageHandler::read_cmd(&conn);
						ans.read(&conn);
						if(ans.ans == Protocol::ANS_ACK) {
							cout << "Newsgroup deleted." << endl;
						} else {
							cout << "Error: " << ans.err << endl;
						}
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
