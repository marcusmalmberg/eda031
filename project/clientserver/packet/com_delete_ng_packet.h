#ifndef COM_DELETE_NG_PACKET_H
#define COM_DELETE_NG_PACKET_H

#include "base_packet.h"

namespace protocol {

	class ComDeleteNgPacket : public BasePacket {
	public:
        void read(const Connection* conn);
        void write(const Connection* conn);
		size_t id;
	};


}

#endif
