#ifndef ANS_GET_ART_PACKET_H
#define ANS_GET_ART_PACKET_H

#include "ans_packet.h"
#include "../article.h"

using namespace news_server;

namespace protocol {

	class AnsGetArtPacket : public AnsPacket {
	public:
        bool read(const Connection* conn);
        void write(const Connection* conn);
		Article a;
	};

}

#endif
