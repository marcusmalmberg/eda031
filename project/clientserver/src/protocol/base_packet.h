#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "protocol.h"
#include "../connection.h"
#include "../message_handler.h"

using namespace client_server;
using namespace news_server;

namespace protocol {
	
	class BasePacket {
	public:
		virtual bool read(const Connection* conn) = 0;
		virtual void write(const Connection* conn) = 0;
	};

}

#endif
