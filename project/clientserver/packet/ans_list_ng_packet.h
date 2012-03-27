#ifndef ANS_LIST_NG_PACKET_H
#define ANS_LIST_NG_PACKET_H

#include <vector>
#include "base_packet.h"

namespace news_server {

	class AnsListNgPacket : public BasePacket {
	public:
		vector<Newsgroup> ngs;
	};

}

#endif
