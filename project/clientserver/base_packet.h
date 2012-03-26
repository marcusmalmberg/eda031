#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include <iostream>

using namespace std;

namespace news_server {
	
	class BasePacket {
	friend BasePacket& operator>>(const istream& in, BasePacket& bp);
	friend ostream& operator<<(ostream& out, const BasePacket& bp);	
	public:
		size_t INVALID_TOKEN = -1;
	private:
		size_t type;
		virtual void read_data(const istream& in) = 0;
		virtual void write_data(ostream& out) = 0;
		size_t read_num(const istream& in);
		string read_string(const istream& in);
		void write_num(ostream& out, const size_t n);
		void write_string(ostream& out, const string& s);
	};

}

#endif
