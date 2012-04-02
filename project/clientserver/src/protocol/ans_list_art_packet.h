#ifndef ANS_LIST_ART_PACKET_H
#define ANS_LIST_ART_PACKET_H

#include <vector>

#include "ans_packet.h"
#include "../article.h"

using namespace news_server;

namespace protocol {

	class AnsListArtPacket : public AnsPacket {
	public:
        bool read(const Connection* conn);
        void write(const Connection* conn);
		vector<Article> arts;
	};

}

#endif
