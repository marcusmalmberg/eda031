#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "protocol.h"
#include "message_handler.h"

using namespace std;
using namespace client_server;

namespace news_server {
	
	class BasePacket {
	public:
		virtual void read(const Connection* conn) = 0;
		virtual void write(const Connection* conn) = 0;
	};

}

#endif
