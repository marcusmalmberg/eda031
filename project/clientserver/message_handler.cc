#include "message_handler.h"

namespace news_server {

	size_t MessageHandler::read_num() {
		read_int();
		return read_int();
	}

	string MessageHandler::read_str() {
		read_int();
		int size = read_int();
		string s;
		s.capacity(size);
		for (int i = 0; i < size; ++i) {
			s[i] = conn.read();;
		}
	}

	void MessageHandler::write_num(const size_t n) {
		write_int(Protocol::PAR_NUM);
		write_int(n);
	}

	void MessageHandler::write_str(const string& s) {
		write_int(Protocol::PAR_STRING);
		write_int(s.size());
		for (auto i = s.begin(); i != s.end(); ++i) {
			conn.write(*i);
		}
	}

	int read_int() {
		unsigned char c1 = conn.read();
		unsigned char c2 = conn.read();
		unsigned char c3 = conn.read();
		unsigned char c4 = conn.read();
		return b1 << 24 | b2 << 16 |b3 << 8 | b4;
	}
	
	void write_int(int i) {
		conn.write((i >> 24) & 0xFF);
		conn.write((i >> 16) & 0xFF);
		conn.write((i >> 8) & 0xFF);
		conn.write((i >> 0) & 0xFF);
	}

}
