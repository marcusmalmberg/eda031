#include <sstream>

#include "message_handler.h"
#include "protocol.h"

using namespace protocol;

namespace news_server {

	size_t MessageHandler::read_num(const Connection* conn) {
		read_cmd(conn);
		return read_int(conn);
	}

	string MessageHandler::read_str(const Connection* conn) {
		MessageHandler::read_cmd(conn);
		int size = MessageHandler::read_int(conn);
		ostringstream oss;
		for (int i = 0; i < size; ++i) {
			oss << conn->read();
		}
		return oss.str();
	}

	void MessageHandler::write_num(const Connection* conn, const size_t n) {
		MessageHandler::write_cmd(conn, Protocol::PAR_NUM);
		MessageHandler::write_int(conn, n);
	}

	void MessageHandler::write_str(const Connection* conn, const string& s) {
		MessageHandler::write_cmd(conn, Protocol::PAR_STRING);
		MessageHandler::write_int(conn, s.size());
		for (auto i = s.begin(); i != s.end(); ++i) {
			conn->write(*i);
		}
	}

	size_t MessageHandler::read_cmd(const Connection* conn) {
		return MessageHandler::read_int(conn);
	}

	void MessageHandler::write_cmd(const Connection* conn, const size_t cmd) {
		MessageHandler::write_int(conn, cmd);
	}

	int MessageHandler::read_int(const Connection* conn) {
		unsigned char c1 = conn->read();
		unsigned char c2 = conn->read();
		unsigned char c3 = conn->read();
		unsigned char c4 = conn->read();
		return c1 << 24 | c2 << 16 | c3 << 8 | c4;
	}
	
	void MessageHandler::write_int(const Connection* conn, const int i) {
		conn->write((i >> 24) & 0xFF);
		conn->write((i >> 16) & 0xFF);
		conn->write((i >> 8) & 0xFF);
		conn->write((i >> 0) & 0xFF);
	}

}
