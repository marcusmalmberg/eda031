#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <string>

#include "connection.h"

using namespace std;
using namespace client_server;

namespace news_server {

	class MessageHandler {
	public:
		static size_t read_num(const Connection* conn);
		static string read_str(const Connection* conn);
		static void write_num(const Connection* conn, const size_t n);
		static void write_str(const Connection* conn, const string& s);
		static size_t read_cmd(const Connection* conn);
		static void write_cmd(const Connection* conn, const size_t cmd);
	private:
		static int read_int(const Connection* conn);
		static void write_int(const Connection* conn, int i);
	};

}

#endif
