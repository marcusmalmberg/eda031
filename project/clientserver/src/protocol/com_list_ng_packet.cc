#include "com_list_ng_packet.h"

namespace protocol {

	bool ComListNgPacket::read(const Connection* conn) {
		if (MessageHandler::read_cmd(conn) != Protocol::COM_END) {
			return false;
		}
		return true;
	}

	void ComListNgPacket::write(const Connection* conn) {
		MessageHandler::write_cmd(conn, Protocol::COM_LIST_NG);
		MessageHandler::write_cmd(conn, Protocol::COM_END);
	}

}
