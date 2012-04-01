#ifndef COM_LIST_NG_PACKET_H
#define COM_LIST_NG_PACKET_H

#include "base_packet.h"

namespace protocol {

	class ComListNgPacket : public BasePacket {
	public:
        void read(const Connection* conn);
		void write(const Connection* conn);
	};

}

#endif
