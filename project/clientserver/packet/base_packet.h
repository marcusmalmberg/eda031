#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include "../protocol.h"

using namespace client_server;

namespace protocol {
	
	class BasePacket {
	public:
		virtual void read(const Connection* conn) = 0;
		virtual void write(const Connection* conn) = 0;
	};

}

#endif
