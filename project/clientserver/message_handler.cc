#include "message_handler.h"
#include "protocol.h"

namespace news_server {

	static size_t MessageHandler::read_num(const Connection* conn) {
		read_int(conn);
		return read_int(conn);
	}

	static string MessageHandler::read_str(const Connection* conn) {
		read_int(conn);
		int size = read_int(conn);
		string s;
		s.capacity(size);
		for (int i = 0; i < size; ++i) {
			s[i] = conn->read(conn);
		}
	}

	static void MessageHandler::write_num(const Connection* conn, const size_t n) {
		write_int(conn, Protocol::PAR_NUM);
		write_int(conn, n);
	}

	static void MessageHandler::write_str(const Connection* conn, const string& s) {
		write_int(conn, Protocol::PAR_STRING);
		write_int(conn, s.size());
		for (auto i = s.begin(); i != s.end(); ++i) {
			conn->write(conn, *i);
		}
	}

	static int read_int(const Connection* conn) {
		unsigned char c1 = conn->read();
		unsigned char c2 = conn->read();
		unsigned char c3 = conn->read();
		unsigned char c4 = conn->read();
		return b1 << 24 | b2 << 16 |b3 << 8 | b4;
	}
	
	static void write_int(const Connection* conn, int i) {
		conn->write((i >> 24) & 0xFF);
		conn->write((i >> 16) & 0xFF);
		conn->write((i >> 8) & 0xFF);
		conn->write((i >> 0) & 0xFF);
	}

}
