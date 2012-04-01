#ifndef COM_GET_ART_PACKET_H
#define COM_GET_ART_PACKET_H

#include "base_packet.h"

namespace protocol {

	class ComGetArtPacket : public BasePacket {
	public:
        void read(const Connection* conn);
        void write(const Connection* conn);
        size_t ng_id;
		size_t art_id;
	};

}

#endif
