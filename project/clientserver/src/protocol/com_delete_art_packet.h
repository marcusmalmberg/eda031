#ifndef COM_DELETE_ART_PACKET_H
#define COM_DELETE_ART_PACKET_H

#include "base_packet.h"

namespace protocol {

	class ComDeleteArtPacket : public BasePacket {
	public:
        bool read(const Connection* conn);
        void write(const Connection* conn);
		size_t ng_id;
		size_t art_id;
	};


}

#endif
