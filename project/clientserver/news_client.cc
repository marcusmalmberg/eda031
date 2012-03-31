#include "connection.h"
#include "connectionclosedexception.h"
#include "message_handler.h"
#include "packet/com_list_ng_packet.h"
#include "packet/com_list_art_packet.h"
#include "packet/ans_list_ng_packet.h"
#include "packet/ans_list_art_packet.h"

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
				if (cin >> cmd) {
					size_t id = atoi(cmd.c_str());
					ComListArtPacket com;
					com.id = id;
					com.write(conn);
					AnsListArtPacket ans;
					ans.read(conn);
					for_each(ans.arts.begin(), ans.arts.end(), [] (Article a) {
						cout << a.id << ". " << a.title << " From: " << a.author << endl;
					});
				} else {
					ComListNgPacket com;
					com.write(conn);
					AnsListNgPacket ans;
					ans.read(conn);
					for_each(ans.ngs.begin(), ans.ngs.end(), [] (Newsgroup ng) {
						cout << ng.id << ". " << ng.name << endl;
					});
				}
			} else if (cmd == "read") {

			} else if (cmd == "quit") {
				break;
			}
		} catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}
