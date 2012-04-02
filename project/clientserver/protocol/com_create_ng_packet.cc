#include "com_create_ng_packet.h"

namespace protocol {

	bool ComCreateNgPacket::read(const Connection* conn) {
		name = MessageHandler::read_str(conn);
		if (MessageHandler::read_cmd(conn) != Protocol::COM_END) {
			return false;
		}
		return true;
	}

	void ComCreateNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_CREATE_NG);
		MessageHandler::write_str(conn, name);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
