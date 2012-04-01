#include "com_get_art_packet.h"

namespace protocol {

	void ComGetArtPacket::read(const Connection* conn) {
		ng_id = MessageHandler::read_num(conn);
		art_id = MessageHandler::read_num(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComGetArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_GET_ART);
		MessageHandler::write_num(conn, ng_id);
		MessageHandler::write_num(conn, art_id);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
