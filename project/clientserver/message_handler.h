#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>
#include "protocol.h"
#include "newsgroup.h"
#include "article.h"

using namespace std;

namespace news_server {

	class MessageHandler {
	public:
		MessageHandler(Connection c) : conn(c);
		size_t read_num();
		string read_str();
		void write_num(const size_t n);
		void write_str(const string& s);
	private:
		int read_int();
		void write_int(int i);
		Connection conn;
	};

}

#endif
