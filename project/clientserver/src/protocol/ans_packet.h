#ifndef ANS_PACKET_H
#define ANS_PACKET_H

#include "base_packet.h"

namespace protocol {

	class AnsPacket : public BasePacket {
	public:
		size_t ans;
		size_t err;
	};

}

#endif
