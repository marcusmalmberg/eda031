#ifndef COM_CREATE_NG_PACKET_H
#define COM_CREATE_NG_PACKET_H

#include <string>

#include "base_packet.h"

using namespace std;

namespace protocol {

	class ComCreateNgPacket : public BasePacket {
	public:
        void read(const Connection* conn);
        void write(const Connection* conn);
		string name;
	};


}

#endif
