#ifndef ANS_CREATE_NG_PACKET_H
#define ANS_CREATE_NG_PACKET_H

#include "base_packet.h"

namespace news_server {

	class AnsListNgPacket : public BasePacket {
	public:
		size_t ans;
		size_t err;
	};

}

#endif
