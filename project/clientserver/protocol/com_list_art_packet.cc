#include "com_list_art_packet.h"

namespace protocol {

	void ComListArtPacket::read(const Connection* conn) {
		id = MessageHandler::read_num(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComListArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_LIST_ART);
		MessageHandler::write_num(conn, id);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
