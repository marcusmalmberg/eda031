#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include <iostream>

using namespace std;
using namespace client_server;

namespace news_server {
	
	class BasePacket {
	public:
		//BasePacket(MessageHandler h) : handler(h);
		//virtual void read() = 0;
		//virtual void write() = 0;
		virtual void read(Connection* conn) = 0;
		virtual void write(Connection* conn) = 0;
	private:
		//MessageHandler handler;
	};

}

#endif
