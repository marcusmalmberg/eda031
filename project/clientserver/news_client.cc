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
	
	cout << "Welcome! If this is your first time you can see a list of available commands by running the command \"help\"." << endl;

	string cmd;
	while (cin >> cmd) {
		try {
			if (cmd == "list") {
				cin >> cmd;
				if (cmd != "ngs") {    // LIST_ART
					size_t id = atoi(cmd.c_str());
					if ( !id && cmd != "0" ) {
						cout << "Expected an integer. Type \"help\" if you need to see the commands" << endl;
						continue;
					}
					cout << "Listing articles for ng with id: " << cmd << endl;
					ComListArtPacket com;
					com.id = id;
					com.write(&conn);
					AnsListArtPacket ans;
					MessageHandler::read_cmd(&conn);
					ans.read(&conn);
					if(ans.ans == Protocol::ANS_ACK) {
						for_each(ans.arts.begin(), ans.arts.end(), [] (Article a) {
							cout << a.id << ". " << a.title << endl;
						});
					} else {
						cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
					}
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
				size_t ng_id;
				if(!(cin >> ng_id)) {
					cout << "Expected first argument to be integer. Type \"help\" if you need to see the commands" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				size_t art_id;
				if(!(cin >> art_id)) {
					cout << "Expected second argument to be integer. Type \"help\" if you need to see the commands" << endl;
					cin.clear();
					cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				ComGetArtPacket com;
				com.ng_id = ng_id;
				com.art_id = art_id;
				com.write(&conn);
				AnsGetArtPacket ans;
				MessageHandler::read_cmd(&conn);
				ans.read(&conn);
				if(ans.ans == Protocol::ANS_ACK) {
					cout << ans.a.title << "\t" << ans.a.author << endl;
					cout << ans.a.text << endl;
				} else {
					cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
				}
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
							cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
						}
					} else {		// CREATE_ART
						size_t ng_id;
						if(!(cin >> ng_id)) {
							cout << "Expected first argument to be integer. Type \"help\" if you need to see the commands" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
							continue;
						}
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
							cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
						}
					}
				}
			} else if (cmd == "delete") {
				if (cin >> cmd) {
					if (cmd == "ng") {		// DELET_NG
						size_t id;
						if(!(cin >> id)) {
							cout << "Expected argument to be integer. Type \"help\" if you need to see the commands" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						ComDeleteNgPacket com;
						com.id = id;
						com.write(&conn);
						AnsDeleteNgPacket ans;
						MessageHandler::read_cmd(&conn);
						ans.read(&conn);
						if(ans.ans == Protocol::ANS_ACK) {
							cout << "Newsgroup deleted." << endl;
						} else {
							cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
						}
					} else {		// DELETE_ART
						size_t ng_id;
						if(!(cin >> ng_id)) {
							cout << "Expected first argument to be integer. Type \"help\" if you need to see the commands" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						size_t art_id;
						if(!(cin >> art_id)) {
							cout << "Expected second argument to be integer. Type \"help\" if you need to see the commands" << endl;
							cin.clear();
							cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
							continue;
						}
						ComDeleteArtPacket com;
						com.ng_id = ng_id;
						com.art_id = art_id;
						com.write(&conn);
						AnsDeleteArtPacket ans;
						MessageHandler::read_cmd(&conn);
						ans.read(&conn);
						if(ans.ans == Protocol::ANS_ACK) {
							cout << "Article deleted." << endl;
						} else {
							cout << "Error: " << Protocol::getTextualError(ans.err) << endl;
						}
					}
				}
			} else if (cmd == "quit") {
				break;
			} else if (cmd == "help") {
				cout << "list ngs" << "\n\t" << "Lists all newsgroups." << "\n" <<endl;
				cout << "create ng <newsgroup name>" << "\n\t" << "Creates a newsgroup with the specified name." << "\n" <<endl;
				cout << "delete ng <newsgroup id>" << "\n\t" << "Deletes the newsgroup with the specified id." << "\n" <<endl;
				cout << "list <newsgroup id>" << "\n\t" << "Lists all articles in the newsgroup with the specified id." << "\n" <<endl;
				cout << "create art <newsgroup id> <article title> <article author> <article text>" << "\n\t" << "Creates an article in the specified newsgroup with title, author and text." << "\n" <<endl;
				cout << "delete art <newsgroup id> <article id>" << "\n\t" << "Deletes an article in the specified newsgroup with the specified id." << "\n" <<endl;
				cout << "read <newsgroup id> <article id>" << "\n\t" << "Reads an article in the specified newsgroup with the specified id." << "\n" <<endl;
				cout << "quit" << "\n\t" << "Exits the program." << "\n" <<endl;
				cout << "help" << "\n\t" << "Shows this list of commands." << "\n" <<endl;
			}
		} catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}
