#include "com_delete_art_packet.h"

namespace protocol {

	void ComDeleteArtPacket::read(const Connection* conn) {
		ng_id = MessageHandler::read_num(conn);
		art_id = MessageHandler::read_num(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComDeleteArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_DELETE_ART);
		MessageHandler::write_num(conn, ng_id);
		MessageHandler::write_num(conn, art_id);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
