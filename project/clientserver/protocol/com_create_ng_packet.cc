#include "com_create_ng_packet.h"

namespace protocol {

	void ComCreateNgPacket::read(const Connection* conn) {
		name = MessageHandler::read_str(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComCreateNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_CREATE_NG);
		MessageHandler::write_str(conn, name);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
