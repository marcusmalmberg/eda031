#ifndef ANS_DELETE_ART_PACKET_H
#define ANS_DELETE_ART_PACKET_H

#include "ans_packet.h"

namespace protocol {

	class AnsDeleteArtPacket : public AnsPacket {
	public:
        bool read(const Connection* conn);
        void write(const Connection* conn);
	};

}

#endif
