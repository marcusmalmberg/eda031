#ifndef COM_LIST_ART_PACKET_H
#define COM_LIST_ART_PACKET_H

#include "base_packet.h"

namespace protocol {

	class ComListArtPacket : public BasePacket {
	public:
        bool read(const Connection* conn);
        void write(const Connection* conn);
		size_t id;
	};

}

#endif
