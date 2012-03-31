#include "message_handler.h"
#include "protocol.h"

using namespace protocol;

namespace news_server {

	size_t MessageHandler::read_num(const Connection* conn) {
		read_cmd(conn);
		return read_int(conn);
	}

	string MessageHandler::read_str(const Connection* conn) {
		read_cmd(conn);
		int size = read_int(conn);
		string s;
		s.reserve(size);
		for (int i = 0; i < size; ++i) {
			s[i] = conn->read();
		}
		return s;
	}

	void MessageHandler::write_num(const Connection* conn, const size_t n) {
		write_cmd(conn, Protocol::PAR_NUM);
		write_int(conn, n);
	}

	void MessageHandler::write_str(const Connection* conn, const string& s) {
		write_cmd(conn, Protocol::PAR_STRING);
		write_int(conn, s.size());
		for (auto i = s.begin(); i != s.end(); ++i) {
			conn->write(*i);
		}
	}

	size_t MessageHandler::read_cmd(const Connection* conn) {
		return read_int(conn);
	}

	void MessageHandler::write_cmd(const Connection* conn, const size_t cmd) {
		write_int(conn, cmd);
	}

	int read_int(const Connection* conn) {
		unsigned char c1 = conn->read();
		unsigned char c2 = conn->read();
		unsigned char c3 = conn->read();
		unsigned char c4 = conn->read();
		return c1 << 24 | c2 << 16 | c3 << 8 | c4;
	}
	
	void write_int(const Connection* conn, int i) {
		conn->write((i >> 24) & 0xFF);
		conn->write((i >> 16) & 0xFF);
		conn->write((i >> 8) & 0xFF);
		conn->write((i >> 0) & 0xFF);
	}

}
