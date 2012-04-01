#include "com_delete_ng_packet.h"

namespace protocol {

	void ComDeleteNgPacket::read(const Connection* conn) {
		id = MessageHandler::read_num(conn);
		MessageHandler::read_cmd(conn);
	}

	void ComDeleteNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_DELETE_NG);
		MessageHandler::write_num(conn, id);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
