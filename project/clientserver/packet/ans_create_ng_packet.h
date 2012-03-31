#ifndef ANS_CREATE_NG_PACKET_H
#define ANS_CREATE_NG_PACKET_H

#include "ans_packet.h"

namespace protocol {

	class AnsCreateNgPacket : public AnsPacket {
	public:
		void read(const Connection* conn);
		void write(const Connection* conn);
	};

}

#endif
