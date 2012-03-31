#ifndef COM_CREATE_NG_PACKET_H
#define COM_CREATE_NG_PACKET_H

#include "base_packet.h"

using namespace std;

namespace news_server {

	class ComCreateNgPacket : public BasePacket {
	public:
		string name;
	};


}

#endif
