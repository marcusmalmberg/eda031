#ifndef COM_CREATE_ART_PACKET_H
#define COM_CREATE_ART_PACKET_H

#include <string>

#include "base_packet.h"

using namespace std;

namespace protocol {

	class ComCreateArtPacket : public BasePacket {
	public:
        void read(const Connection* conn);
        void write(const Connection* conn);
		size_t ng_id;
        string title;
        string author;
        string text;
	};


}

#endif
