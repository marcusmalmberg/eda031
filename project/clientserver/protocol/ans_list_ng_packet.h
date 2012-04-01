#ifndef ANS_LIST_NG_PACKET_H
#define ANS_LIST_NG_PACKET_H

#include <vector>

#include "ans_packet.h"
#include "../newsgroup.h"

using namespace news_server;

namespace protocol {

	class AnsListNgPacket : public AnsPacket {
	public:
        void read(const Connection* conn);
        void write(const Connection* conn);
		vector<Newsgroup> ngs;
	};

}

#endif
