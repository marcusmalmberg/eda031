#include "com_create_art_packet.h"

namespace protocol {

	bool ComCreateArtPacket::read(const Connection* conn) {
		ng_id = MessageHandler::read_num(conn);
		title = MessageHandler::read_str(conn);
		author = MessageHandler::read_str(conn);
		text = MessageHandler::read_str(conn);
		if (MessageHandler::read_cmd(conn) != Protocol::COM_END) {
			return false;
		}
		return true;
	}

	void ComCreateArtPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_CREATE_ART);
		MessageHandler::write_num(conn, ng_id);
		MessageHandler::write_str(conn, title);
		MessageHandler::write_str(conn, author);
		MessageHandler::write_str(conn, text);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
